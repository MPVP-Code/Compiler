#ifndef AST_ASSIGNMENT_H
#define AST_ASSIGNMENT_H

//#include "../ast.hpp"
#include "ast_variable.hpp"
#include "ast_scope.hpp"
#include <string>



class Constant : public Node {
private:
    int value;

public:
    Constant(int _value) : value(_value) {
        this->type = "Constant";
    }

    int getValue() {
        return this->value;
    }
};

class Assign : public Node {
private:
    Variable *destination;
    Node *source;

public:
    Assign(Variable *_destination, Node *_source) : destination(_destination), source(_source) {
        this->type = "Assign";
    }

    void generate_var_maps(Scope* parent) override {
        if (this->destination->declaration) {
            parent->var_map[destination->name] = destination;

        } else {
            Variable* old_destination = this->destination;
            this->destination = parent->var_map[old_destination->name];
            delete old_destination;
        }
        source->generate_var_maps(parent);
    }

//    std::string compileToMIPS() const override {
//        std::string result = "";
//        if (source->type == "Constant") {
//            Constant *constant = (Constant*) source;
//            std::string hexValue = Global::intToHex(constant->getValue());
//            int registerNumber = Global::getRegisterNumberForVariable(destination->getName());
//            result = "li $" + std::to_string(registerNumber) + ", " + hexValue;
//        }
//
//        return result;
//    }
};

#endif
