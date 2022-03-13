//
// Created by michal on 4. 3. 2022.
//

#ifndef AST_SCOPE_HPP
#define AST_SCOPE_HPP

#include "ast_node.hpp"

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>

class Variable: public Node{
public:
    std::string variable_type;
    std::string name;
    bool declaration;
    Variable(const std::string &_type, const std::string &_name, const bool _declaration);
};


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
//private:
//    static std::unordered_map<std::string, int> registersMapping;
//    static int currentRegister;
public:
    //Inherits branches & type

    Global() {
        this->type = "Global";
        this->parent_scope = NULL;
    }

//    //Has gettype
//
//    virtual double compile() const override{
//        throw std::runtime_error("Global compile not implemented.");
//    }
//
//    virtual double print() const override{
//        throw std::runtime_error("Global print not implemented.");
//    }
//
//    static void initCurrentRegister() {
//        currentRegister = 2;
//    }

//    static int getRegisterNumberForVariable(std::string *variable) {
//        int result = currentRegister;
//        auto iterator = registersMapping.find(*variable);
//        if (iterator == registersMapping.end()) {
//            registersMapping.insert(std::pair<std::string, int>(*variable, currentRegister));
//        } else {
//            result = iterator->second;
//        }
//        currentRegister++;
//        return result;
//    }

//    static std::string intToHex(int i)
//    {
//        std::stringstream stream;
//        stream << "0x" << std::setfill ('0') << std::setw(sizeof(i)) << std::hex << i;
//        return stream.str();
//    }

};

//int Global::currentRegister = 0;
//std::unordered_map<std::string, int> map;
//std::unordered_map<std::string, int> Global::registersMapping = map;
#endif


