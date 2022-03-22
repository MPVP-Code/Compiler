#include "ast_scope.hpp"
#include "ast_func.hpp"

#include <string>

Scope::Scope() {
    this->type = "Scope";
    this->branches = {};
}

void Scope::generate_var_maps(Node* parent) {

    Scope *parentScope = (Scope*) parent;
    for (auto &node: this->branches) {
        if (node->type == "Scope") {
            Scope *scope = (Scope *) node;
            scope->parent_scope = this;
            scope->generate_var_maps(this);

        } else if (node->type == "Variable" ){
            auto temp = (Variable*) node;
            if(temp->declaration) {
                this->var_map[temp->name] = temp;
            }
            else{
                node = this->var_map[temp->name] = temp;
            }
        }
        else{
            node->generate_var_maps(this);
        }

    }

};

std::vector<Node*>* Scope::getBranches() {
    return &(this->branches);
};

std::string Scope::compileToMIPS() const {
    throw std::runtime_error(this->type + " compileToMIPS not implemented.");
}


Global::Global() {
    this->type = "Global";
    this->parent_scope = NULL;
}

std::string Global::compileToMIPS() const {
    std::string result = "";

    for (Node *statement: this->branches) {
        std::cerr << "statement->get_type(): " << statement->get_type()  << "subtype: " << statement->getSubtype() << std::endl;
        if (statement->get_type().compare("FunctionDeclaration") == 0 || statement->getSubtype().compare("FunctionDeclaration") == 0) {
            FunctionDeclaration *function = (FunctionDeclaration*) statement;
            result += ".globl " + *(function->getName()) + "\n";
        }
    }

    for (Node *statement : this->branches) {
        result += statement->compileToMIPS() + "\n";
    }

    return result;
}