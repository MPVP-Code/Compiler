#include "ast_variable.h"
#include "ast_scope.h"
#include "ast_node.h"
#include "ast_arithmetic.h"
#include "ast_assignment.h"
#include <string>


Constant::Constant(int _value) : value(_value) {
    this->type = "Constant";
}

int Constant::getValue() {
    return this->value;
}

Assign::Assign(Variable *_destination, Node *_source) : destination(_destination), source(_source) {
    this->type = "Assign";
}

void Assign::generate_var_maps(Node *parent) {
    Scope *parentScope = (Scope*) parent;
    if (this->destination->declaration) {
        parentScope->var_map[destination->name] = destination;
    } else {
        Variable *old_destination = this->destination;
        this->destination = parentScope->var_map[old_destination->name];
    }
    source->generate_var_maps(parent);
}

std::string Assign::compileToMIPS() const {
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
};

