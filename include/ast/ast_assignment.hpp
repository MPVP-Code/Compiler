#ifndef AST_ASSIGNMENT_H
#define AST_ASSIGNMENT_H

#include "ast_node.hpp"
#include "ast_type.hpp"
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
    Assign(Variable *_destination, Node *_source): destination(_destination), source(_source) {
        this->type = "Assign";
    }

    std::string compileToMIPS() const override {
        std::string result = "";
        if (source->type == "Constant") {
            Constant *constant = (Constant*) source;
            std::string hexValue = Global::intToHex(constant->getValue());
            int registerNumber = Global::getRegisterNumberForVariable(destination->getName());
            result = "li $" + std::to_string(registerNumber) + ", " + hexValue;
        }

        return result;
    }
};

/*class Declare : Node {

public:
    Variable *destination;
    Node *source;

    Declare(Variable *dest, Node *src){
        this->destination = dest;
        this->source = src;
        this->type = "Assign";
    }
};*/

/*class Add : Node {
private:
    Variable *destination;
    Node *value;
};*/

#endif
