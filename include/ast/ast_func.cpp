#include "ast_func.hpp"
#include "ast_node.hpp"
#include "ast_stack.hpp"

#include <vector>

FunctionDeclaration::FunctionDeclaration(){  //std::string _return_type, std::string _name, std::vector<Node*> _statements
    //Type specification
    this->type = "Scope";
    this->subtype = "FunctionDeclaration";
}

std::string FunctionDeclaration::compileToMIPS(const Node *parent_scope) const {
    std::cerr << "Compiling function " << this->name << std::endl;
    std::string result = this->name + ":\n.set noreorder\n";

    for (Node *statement : statements) {
        std::cerr << "Compiling statement " << statement->get_type() << std::endl;
        std::string compiledCode = statement->compileToMIPS(this);
        if (compiledCode.length() != 0) {
            result += compiledCode + "\n";
        }
    }
    result = result.substr(0, result.length() - 1);

    //Appends implicit returns for void and it types
    if (return_type == "void") {
        result += "\njr $31\nnop";
    }if (return_type == "int") {
        //implicit error code 0
        result += "\nli $v0, 0\n";
        result += "\njr $31\nnop\n";
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

