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
        this->destination = parentScope->resolve_variable_scope(this->destination->name);
    }

    //Source varmapping
    if(this->source->type == "Variable"){
        auto var = (Variable*) this->source;
        this->source = parentScope->resolve_variable_scope(var->name);
    }
    else{
        source->generate_var_maps(parent);
    }

    //type propagation
    this->data_type = source->data_type;
}

void Constant::generate_var_maps(Node *parent) {
    return;
}

std::string Assign::compileToMIPS() const {
    std::string result = "";
    if (source->type == "Constant") {
        std::cerr << "Compiling the constant 1" << std::endl;
        Constant *constant = (Constant *) source;
        std::cerr << "Compiling the constant 2" << std::endl;
        std::string hexValue = RegisterAllocator::intToHex(constant->getValue());
        std::cerr << "Compiling the constant 3" << std::endl;
        //std::cerr << "Destination getName " << *(destination->getName()) << std::endl;
        std::cerr << "Destination data_type " << destination->data_type << std::endl;
        std::cerr << "Destination type " << destination->type << std::endl;
        std::cerr << "Destination getType " << destination->get_type() << std::endl;
        std::cerr << "Destination variable type " << destination->getVariableType() << std::endl;
        int registerNumber = RegisterAllocator::getRegisterNumberForVariable(destination->getName());
        std::cerr << "Compiling the constant 4" << std::endl;
        result = "li $" + std::to_string(registerNumber) + ", " + hexValue;
    } else if (source->type == "Addition") {
        Addition *addition = (Addition *) source;
        std::cerr << "Compiling the addition" << std::endl;
        std::cerr << "Compiling the addition is left int" << addition->isLInt() << std::endl;
        std::cerr << "Compiling the addition is right int" << addition->isRInt() << std::endl;
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

