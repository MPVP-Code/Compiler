#include "ast_func.hpp"
#include "ast_node.hpp"
#include "ast_stack.hpp"

#include <vector>

FunctionDeclaration::FunctionDeclaration(){  //std::string _return_type, std::string _name, std::vector<Node*> _statements
    //Type specification
    this->type = "Scope";
    this->subtype = "FunctionDeclaration";
    this->forward_declaration = false;
}

std::string FunctionDeclaration::compileToMIPS(const Node *parent_scope) const {
    std::cerr << "Compiling function " << this->name << std::endl;
    std::string result = "";

    //Do not compile forward declarations
    if (!forward_declaration) {
        result = this->name + ":\n.set noreorder\n";

        for (Node *statement: statements) {
            std::cerr << "Compiling statement " << statement->get_type() << std::endl;
            std::string compiledCode = statement->compileToMIPS(this);
            if (compiledCode.length() != 0) {
                result += compiledCode;
            }
        }
        result = result.substr(0, result.length() - 1);

        //Appends implicit returns for void and int types
        if (return_type == "void") {
            result += "\njr $31\nnop";
        }
        if (return_type == "int") {
            //implicit error code 0
            result += "\nli $v0, 0\n";
            result += "jr $31\nnop\n";
        }
    }
    return result;
};

std::string* FunctionDeclaration::getName() {
    return &(this->name);
}

FunctionDeclaration::~FunctionDeclaration() {}

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

std::string FunctionCall::generate_function_signature() const {
    return function_name +"():";
}

std::string FunctionCall::compileToMIPS(const Node *parent_scope) const {
    std::string result  = "";

    //Load parameters into registers
    int idx = 0;
    for (auto param : *arguments){
        if (idx<4){
            result += load_mapped_variable((Scope*) parent_scope, param->get_intermediate_variable(), "$a" + std::to_string(idx)) + "\n";
        }else if (idx < 12){
            result += load_mapped_variable((Scope*) parent_scope, param->get_intermediate_variable(), "$t" + std::to_string(idx-4)) + "\n";
        }
    }

    //Save return address
    //result += "sw $ra, "+ to_string(this->stack_frame_size) + "($sp)";

    //Jump
    result += "jal " + this->generate_function_signature() + "\n";

    //Restore return address

    return result;
}

