#include "ast_variable.hpp"
#include "ast_scope.hpp"
#include "ast_node.hpp"
#include "ast_arithmetic.hpp"
#include "ast_assignment.hpp"
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

    //Destination var mapping
    if (this->destination->declaration) {
        parentScope->var_map[destination->name] = destination;
    } else {
        this->destination = resolve_variable_scope(this->destination->name, parentScope);
    }

    //Source varmapping
    if(this->source->type == "Variable"){
        auto var = (Variable*) this->source;
        this->source = resolve_variable_scope(var->name, parentScope);
    }
    else{
        source->generate_var_maps(parent);
    }

    //type propagation
    this->data_type = destination->data_type;
}

void Constant::generate_var_maps(Node *parent) {
    return;
}

std::string Assign::compileToMIPS() const {
    std::string result = "";
    if (destination->data_type == "int") {
        if (source->type == "Constant") {
            Constant *constant = (Constant *) source;
            std::string hexValue = RegisterAllocator::intToHex(constant->getValue());
            int registerNumber = RegisterAllocator::getRegisterNumberForVariable(destination->getName());
            result = "li $" + std::to_string(registerNumber) + ", " + hexValue;
        } else if (source->type == "BinaryOperator" && source->subtype == "Addition") {
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
    }
    return result;
};

