#include "ast_variable.hpp"
#include "ast_scope.hpp"
#include "ast_node.hpp"
#include "ast_assignment.hpp"
#include "ast_stack.hpp"
#include <string>


Constant::Constant(int _value) : value(_value) {
    this->type = "Constant";
    this->data_type = "int";
}

int Constant::getValue() {
    return this->value;
}

void Constant::generate_var_maps(Node *parent) {
    const_var = allocate_temp_var(parent, data_type);
}

Node* Constant::get_intermediate_variable(){
    return const_var;
}

std::string Constant::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    if (data_type == "int") {
        std::string hexValue = intToHex(value);
        result = "li $15, " + hexValue + "\n";
        result += store_mapped_variable((Scope *) parent_scope, const_var, "$15");
    }
    return result;
}

Assign::Assign(Variable *_destination, Node *_source) : destination(_destination), source(_source) {
    this->type = "Assign";
}

void Assign::generate_var_maps(Node *parent) {
    Scope *parentScope = (Scope *) parent;

    //Destination var mapping
    auto temp = (Node *) this->destination;
    try_replace_variable(temp, parent);
    this->destination = (Variable *) temp;

    //Source varmapping
    try_replace_variable(source, parent);

    //type propagation
    this->data_type = destination->data_type;
}

std::string Assign::compileToMIPS(const Node *parent_scope) const {

    std::string result = "";
    result = source->compileToMIPS(parent_scope);

    if (data_type == "int") {
        Node *src_var = source->get_intermediate_variable();
        result += load_mapped_variable((Scope*) parent_scope, src_var, "$15");
        result += store_mapped_variable((Scope*) parent_scope, destination, "$15");
    }
    return result;
};


//std::string Assign::compileToMIPS(const Node *parent_scope) const {
//
//        } else if (source->type == "Multiplication" ||
//                   (source->type == "BinaryOperator" && source->subtype == "Multiplication")) {
//            Multiplication *multiplication = (Multiplication *) source;
//            if (multiplication->isLInt() && multiplication->isRInt()) {

//            }
//        } else if (source->type == "Division" || (source->type == "BinaryOperator" && source->subtype == "Division")) {
//            Division *division = (Division *) source;
//            if (division->isLInt() && division->isRInt()) {
//                Variable *LVar = (Variable *) division->getL();
//                Variable *RVar = (Variable *) division->getR();
//                int lOpReg = RegisterAllocator::getRegisterNumberForVariable(LVar->getName());
//                int rOpReg = RegisterAllocator::getRegisterNumberForVariable(RVar->getName());
//                int resultReg = RegisterAllocator::getRegisterNumberForVariable(destination->getName());
//                result = "div $" + std::to_string(lOpReg) + ", $" + std::to_string(rOpReg) + "\nmflo $" +
//                         std::to_string(resultReg);
//            }
//        } else if (source->type == "Modulo" || (source->type == "BinaryOperator" && source->subtype == "Modulo")) {
//            Modulo *modulo = (Modulo *) source;
//            if (modulo->isLInt() && modulo->isRInt()) {
//                Variable *LVar = (Variable *) modulo->getL();
//                Variable *RVar = (Variable *) modulo->getR();
//                int lOpReg = RegisterAllocator::getRegisterNumberForVariable(LVar->getName());
//                int rOpReg = RegisterAllocator::getRegisterNumberForVariable(RVar->getName());
//                int resultReg = RegisterAllocator::getRegisterNumberForVariable(destination->getName());
//                result = "div $" + std::to_string(lOpReg) + ", $" + std::to_string(rOpReg) + "\nmfhi $" +
//                         std::to_string(resultReg);
//            }
//        }
//    }
//    return result;
//};

