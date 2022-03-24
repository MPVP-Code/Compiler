#include "ast_variable.hpp"
#include "ast_scope.hpp"
#include "ast_node.hpp"
#include "ast_arithmetic.hpp"
#include "ast_assignment.hpp"
#include <string>


Constant::Constant(int _value) : value(_value) {
    this->type = "Constant";
    this->data_type = "int";
}

int Constant::getValue() {
    return this->value;
}

void Constant::generate_var_maps(Node *parent) {
    return;
}

Assign::Assign(Variable *_destination, Node *_source) : destination(_destination), source(_source) {
    this->type = "Assign";
}

void Assign::generate_var_maps(Node *parent) {
    Scope *parentScope = (Scope*) parent;

    //Destination var mapping
    auto temp = (Node*)this->destination;
    try_replace_variable(temp, parent);
    this->destination = (Variable*) temp;

    //Source varmapping
    try_replace_variable(source, parent);

    //type propagation
    this->data_type = destination->data_type;
}

std::string Assign::compileToMIPS() const {
    std::string result = "";
    if (destination->data_type == "int") {
        if (source->type == "Constant") {
            Constant *constant = (Constant *) source;
            std::string hexValue = RegisterAllocator::intToHex(constant->getValue());
            int registerNumber = RegisterAllocator::getRegisterNumberForVariable(destination->getName());
            result = "li $" + std::to_string(registerNumber) + ", " + hexValue;
        } else if (source->type == "Addition" || (source->type == "BinaryOperator" && source->subtype == "Addition")) {
            Addition *addition = (Addition *) source;
            if (addition->isLInt() && addition->isRInt()) {
                Variable *LVar = (Variable *) addition->getL();
                Variable *RVar = (Variable *) addition->getR();
                int lOpReg = RegisterAllocator::getRegisterNumberForVariable(LVar->getName());
                int rOpReg = RegisterAllocator::getRegisterNumberForVariable(RVar->getName());
                int resultReg = RegisterAllocator::getRegisterNumberForVariable(destination->getName());
                result = "add $" + std::to_string(resultReg) + ", $" + std::to_string(lOpReg) + ", $" + std::to_string(rOpReg);
            }
        } else if (source->type == "Subtraction" || (source->type == "BinaryOperator" && source->subtype == "Subtraction")) {
            Subtraction *subtraction = (Subtraction *) source;
            if (subtraction->isLInt() && subtraction->isRInt()) {
                Variable *LVar = (Variable *) subtraction->getL();
                Variable *RVar = (Variable *) subtraction->getR();
                int lOpReg = RegisterAllocator::getRegisterNumberForVariable(LVar->getName());
                int rOpReg = RegisterAllocator::getRegisterNumberForVariable(RVar->getName());
                int resultReg = RegisterAllocator::getRegisterNumberForVariable(destination->getName());
                result = "sub $" + std::to_string(resultReg) + ", $" + std::to_string(lOpReg) + ", $" + std::to_string(rOpReg);
            }
        } else if (source->type == "Multiplication" || (source->type == "BinaryOperator" && source->subtype == "Multiplication")) {
            Multiplication *multiplication = (Multiplication *) source;
            if (multiplication->isLInt() && multiplication->isRInt()) {
                Variable *LVar = (Variable *) multiplication->getL();
                Variable *RVar = (Variable *) multiplication->getR();
                int lOpReg = RegisterAllocator::getRegisterNumberForVariable(LVar->getName());
                int rOpReg = RegisterAllocator::getRegisterNumberForVariable(RVar->getName());
                int resultReg = RegisterAllocator::getRegisterNumberForVariable(destination->getName());
                result = "mult $" + std::to_string(lOpReg) + ", $" + std::to_string(rOpReg) + "\nmflo $" + std::to_string(resultReg);
            }
        } else if (source->type == "Division" || (source->type == "BinaryOperator" && source->subtype == "Division")) {
            Division *division = (Division *) source;
            if (division->isLInt() && division->isRInt()) {
                Variable *LVar = (Variable *) division->getL();
                Variable *RVar = (Variable *) division->getR();
                int lOpReg = RegisterAllocator::getRegisterNumberForVariable(LVar->getName());
                int rOpReg = RegisterAllocator::getRegisterNumberForVariable(RVar->getName());
                int resultReg = RegisterAllocator::getRegisterNumberForVariable(destination->getName());
                result = "div $" + std::to_string(lOpReg) + ", $" + std::to_string(rOpReg) + "\nmflo $" + std::to_string(resultReg);
            }
        } else if (source->type == "Modulo" || (source->type == "BinaryOperator" && source->subtype == "Modulo")) {
            Modulo *modulo = (Modulo *) source;
            if (modulo->isLInt() && modulo->isRInt()) {
                Variable *LVar = (Variable *) modulo->getL();
                Variable *RVar = (Variable *) modulo->getR();
                int lOpReg = RegisterAllocator::getRegisterNumberForVariable(LVar->getName());
                int rOpReg = RegisterAllocator::getRegisterNumberForVariable(RVar->getName());
                int resultReg = RegisterAllocator::getRegisterNumberForVariable(destination->getName());
                result = "div $" + std::to_string(lOpReg) + ", $" + std::to_string(rOpReg) + "\nmfhi $" + std::to_string(resultReg);
            }
        }
    }
    return result;
};

