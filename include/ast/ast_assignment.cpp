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
    std::cerr << "destination->data_type: " << destination->data_type << std::endl;
    if (destination->data_type == "int") {
        std::cerr << "source->type: " << source->type << " source->subtype: " << source->subtype << std::endl;
        if (source->type == "Constant") {
            Constant *constant = (Constant *) source;
            std::string hexValue = RegisterAllocator::intToHex(constant->getValue());
            int registerNumber = RegisterAllocator::getRegisterNumberForVariable(destination->getName());
            result = "li $" + std::to_string(registerNumber) + ", " + hexValue;
        } else if (source->type == "BinaryOperator" && source->subtype == "Addition") {
            Addition *addition = (Addition *) source;
            std::cerr << "addition->isLInt(): " << addition->isLInt() << " addition->isRInt(): " << addition->isRInt();
            std::cerr << "addition->L->get_type(): " << addition->L->get_type() << std::endl;
            std::cerr << "addition->L->data_type: " << addition->L->data_type << std::endl;
            std::cerr << "addition->R->get_type(): " << addition->R->get_type() << std::endl;
            std::cerr << "addition->R->data_type: " << addition->R->data_type << std::endl;
            if (addition->isLInt() && addition->isRInt()) {
                Variable *LVar = (Variable *) addition->getL();
                Variable *RVar = (Variable *) addition->getR();
                int lOpReg = RegisterAllocator::getRegisterNumberForVariable(LVar->getName());
                int rOpReg = RegisterAllocator::getRegisterNumberForVariable(RVar->getName());
                int resultReg = RegisterAllocator::getRegisterNumberForVariable(destination->getName());
                result = "add $" + std::to_string(resultReg) + ", $" + std::to_string(lOpReg) + ", $" + std::to_string(rOpReg);
            }
        } else if (source->type == "BinaryOperator" && source->subtype == "Subtraction") {
            Subtraction *subtraction = (Subtraction *) source;
            if (subtraction->isLInt() && subtraction->isRInt()) {
                Variable *LVar = (Variable *) subtraction->getL();
                Variable *RVar = (Variable *) subtraction->getR();
                int lOpReg = RegisterAllocator::getRegisterNumberForVariable(LVar->getName());
                int rOpReg = RegisterAllocator::getRegisterNumberForVariable(RVar->getName());
                int resultReg = RegisterAllocator::getRegisterNumberForVariable(destination->getName());
                result = "sub $" + std::to_string(resultReg) + ", $" + std::to_string(lOpReg) + ", $" + std::to_string(rOpReg);
            }
        }
    }
    return result;
};

