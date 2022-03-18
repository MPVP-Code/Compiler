#include "ast_func.hpp"
#include "ast_node.hpp"

#include <vector>

FunctionDeclaration::FunctionDeclaration(std::string _return_type, std::string _name, std::vector<Node*> _statements):
    return_type(_return_type), name(_name), statements(_statements) {
    //Type specification
    this->type = "Scope";
    this->subtype = "FunctionDeclaration";
}

std::string FunctionDeclaration::compileToMIPS() const {
    std::string result = this->name + ":\n.set noreorder\n";

    std::cerr << "calling function declaration" << std::endl;

    for (Node *statement : statements) {
        std::cerr << "statement " << statement->get_type() << std::endl;
        result += statement->compileToMIPS() + "\n";
    }

    result += "jr $31\nnop";
    return result;
};

std::string* FunctionDeclaration::getName() {
    return &(this->name);
}

FunctionDeclaration::~FunctionDeclaration() {}

void FunctionDeclaration::generate_var_maps(Node *parent) {}

FunctionCall::FunctionCall(std::string _function_name, std::vector<Node*> _arguments): function_name(_function_name) {
    this->branches = _arguments;
};
