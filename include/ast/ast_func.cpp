#include "ast_func.hpp"
#include "ast_node.hpp"
#include "ast_stack.hpp"

#include <vector>

FunctionDeclaration::FunctionDeclaration(){  //std::string _return_type, std::string _name, std::vector<Node*> _statements
    //Type specification
    this->type = "Scope";
    this->subtype = "FunctionDeclaration";
    this->forward_declaration = false;

    //Allocate one variable for return address
    this->var_map["!ra"] = new Variable("int", "!ra", true);
}

std::string FunctionDeclaration::compileToMIPS(const Node *parent_scope) const {
    std::cerr << "Compiling function " << this->name << std::endl;
    std::string result = "";

    //Do not compile forward declarations
    if (!forward_declaration) {

        //Function signature generation
        result += ".globl " + generate_function_signature() + "\n";
        result += generate_function_signature()+ ":\n";
        result += ".set noreorder\n";

        //Saving passed parameters
        int idx = 4;
        for (auto param : *arguments) {

            result += store_mapped_variable((Scope*)parent_scope, param, "$" + std::to_string(idx) );

            //Two word store - skip register
            if (resolve_variable_size(param->name, (Scope*)parent_scope)>4){
                idx +=2;
            }else{
                idx++;
            }

        }

        //Compile body
        for (Node *statement: statements) {
            std::cerr << "Compiling statement " << statement->get_type() << std::endl;
            std::string compiledCode = statement->compileToMIPS(this);
            if (compiledCode.length() != 0) {
                result += compiledCode + "\n";
            }
        }

        //Appends implicit returns for void and int types
        if (return_type == "void") {
            result += "\njr $31\nnop\n";
        }
        if (return_type == "int") {
            //implicit error code 0
            result += "\nli $v0, 0\n";
            result += "\njr $31\nnop\n";
        }

    }
    return result;
};

std::string* FunctionDeclaration::getName() {
    return &(this->name);
}

FunctionDeclaration::~FunctionDeclaration() {}

std::string FunctionDeclaration::generate_function_signature() const {
    std::string result = name + "(";
    for (auto arg : *arguments){
        result += arg->data_type + ", ";
    }
    result = result.substr(0, result.length() - 1) + ")";
    return result;
}

FunctionCall::FunctionCall(std::string _function_name, std::vector<Node*>* _arguments): function_name(_function_name) {
    this->arguments = _arguments;
};

void FunctionCall::generate_var_maps(Node *parent){

    //Applies varmapping to parameters
    auto scope = (Scope*) parent;
    for(auto param : *this->arguments){
        try_replace_variable(param, scope);
    }
}



std::string FunctionCall::compileToMIPS(const Node *parent_scope) const {
    std::string result  = "";

    //Load parameters into registers
    int idx = 4; // First arg register

    for (auto param : *arguments){
        //Compile code in parameters
        result+= param->compileToMIPS(parent_scope);

        result += load_mapped_variable((Scope*)parent_scope, param->get_intermediate_variable(), "$" + std::to_string(idx) );

        //Two word load - skip register
        if (resolve_variable_size(((Variable*)param->get_intermediate_variable())->name, (Scope*)parent_scope)>4){
            idx +=2;
        }else{
            idx++;
        }

    }

    //Save return address
    Variable* ra = ((Scope*) parent_scope)->var_map["!ra"];
    result+= store_mapped_variable((Scope*)parent_scope, ra , "$ra" );

    //Get corresponding function declaration
    auto declaration = (FunctionDeclaration*)resolve_function_call(function_name, ((Scope*) parent_scope));

    //Jump
    result += "jal " + declaration->generate_function_signature() + "\n";
    result += "nop\n";

    //Restore return address
    result+= load_mapped_variable((Scope*)parent_scope, ra , "$ra" );
    return result;
}


