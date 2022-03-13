#ifndef AST_ASSIGNMENT_H
#define AST_ASSIGNMENT_H

#include "ast_variable.hpp"
#include "ast_scope.hpp"
#include "../register_allocator.h"
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

    void generate_var_maps(Scope *parent) override {
        if (this->destination->declaration) {
            parent->var_map[destination->name] = destination;

        } else {
            Variable *old_destination = this->destination;
            this->destination = parent->var_map[old_destination->name];
            delete old_destination;
        }
        source->generate_var_maps(parent);
    }

    std::string compileToMIPS() const override {
        std::string result = "";
        if (source->type == "Constant") {
            Constant *constant = (Constant *) source;
            std::string hexValue = RegisterAllocator::intToHex(constant->getValue());
            int registerNumber = RegisterAllocator::getRegisterNumberForVariable(destination->getName());
            result = "li $" + std::to_string(registerNumber) + ", " + hexValue;
        } else if (source->type == "Addition") {
            Addition *addition = (Addition *) source;
            if (addition->isLInt() && addition->isRInt()) {
                Variable *LVar = (Variable *) addition->getL();
                Variable *RVar = (Variable *) addition->getR();
                int lOpReg = RegisterAllocator::getRegisterNumberForVariable(LVar->getName());
                int rOpReg = RegisterAllocator::getRegisterNumberForVariable(RVar->getName());
                int resultReg = RegisterAllocator::getRegisterNumberForVariable(destination->getName());
                result = "addu $" + std::to_string(resultReg) + ", $" + std::to_string(lOpReg) + ", $" + std::to_string(rOpReg);
            }
        }

        return result;
    }
};

#endif
