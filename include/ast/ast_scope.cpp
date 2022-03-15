#include "ast_scope.h"

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>


Identifiera::Identifiera(std::string id) {
    this->type = "Identifier";
    this->identifier = id;
}

//Scope::Scope() {
    /*this->type = "Scope";
    this->branches = {};*/
//}

/*void Scope::generate_var_maps(Scope* parent) {
    std::cout << "hello from generate_var_maps" << std::endl;
    /*for (auto node: this->branches) {
        if (node->type == "Scope") {
            Scope *scope = (Scope *) node;
            scope->parent_scope = this;
            scope->generate_var_maps(this);
        } else if (node->type == "Variable" ){
            auto temp = (Variable*) node;
            if(temp->declaration) {
                parent->var_map[temp->name] = temp;
            }

        }
    }*/
//};

/*class Global : public Scope {
public:
    //Inherits branches & type

    Global() {
        this->type = "Global";
        this->parent_scope = NULL;
    }

    //Has gettype

    virtual double compile() const override{
        throw std::runtime_error("Global compile not implemented.");
    }

    virtual double print() const override{
        throw std::runtime_error("Global print not implemented.");
    }

    virtual std::string compileToMIPS() const {
        std::string result = ".globl f\n";

        for (Node *statement: this->branches) {
            if (statement->get_type().compare("Function") == 0) {
                FunctionDeclaration *function = (FunctionDeclaration*) statement;
                result += ".globl " + *(function->getName());
            }
        }

        for (Node *statement : this->branches) {
            result += statement->compileToMIPS() + "\n";
        }

        return result;
    }

};

#endif


*/