#include "ast_func.hpp"
#include "ast_node.hpp"

#include <vector>

FunctionDeclaration::FunctionDeclaration(std::string _return_type, std::string _name, std::vector<Node*> _statements):
    return_type(_return_type), name(_name){
    //Type specification
    this->statements = _statements;
    this->type = "Scope";
    this->subtype = "FunctionDeclaration";
}

std::string FunctionDeclaration::compileToMIPS() const {
    std::cerr << "Compiling function " << this->name << std::endl;
    std::string result = this->name + ":\n.set noreorder\n";

    for (Node *statement : statements) {
        std::cerr << "Compiling statement " << statement->get_type() << std::endl;
        std::string compiledCode = statement->compileToMIPS();
        if (compiledCode.length() != 0) {
            result += compiledCode + "\n";
        }
    }
    result = result.substr(0, result.length() - 1);

    if (statements[statements.size() - 1]->get_type() != "ReturnExpression") {
        result += "\njr $31\nnop";
    }
    return result;
};

std::string* FunctionDeclaration::getName() {
    return &(this->name);
}

FunctionDeclaration::~FunctionDeclaration() {}

FunctionCall::FunctionCall(std::string _function_name, std::vector<Node*> _arguments): function_name(_function_name) {
    //this->statements = _arguments;
};
