//
// Created by michal on 4. 3. 2022.
//

#ifndef AST_SCOPE_HPP
#define AST_SCOPE_HPP

#include "ast_node.hpp"
#include "ast_variable.hpp"

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>


class Scope : public Node {
public:

    Scope* parent_scope;
    std::map<std::string, Variable *> var_map;

    Scope() {
        this->type = "Scope";
        this->branches = {};
    }

    double compile() const override {
        throw std::runtime_error("Scope compile not implemented.");
    }

    double print() const override {
        throw std::runtime_error("Scope compile print not implemented.");
    }

    void generate_var_maps(Scope* parent) override{
        for (auto node: branches) {
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

            {
                node->generate_var_maps(this);
            }
        }
    }


};

class Global : public Scope {
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



};

#endif


