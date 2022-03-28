#include "ast_variable.hpp"
#include "ast_scope.hpp"
#include "ast_node.hpp"
#include "ast_assignment.hpp"
#include "ast_stack.hpp"
#include "ast_operator.hpp"
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

ConstantFloat::ConstantFloat(float _value): value(_value) {
    this->type = "Constant";
    this->data_type = "float";
}

float ConstantFloat::getValue() {
    return this->value;
}

Variable* ConstantFloat::getConstVar() {
    return this->const_var;
}

void ConstantFloat::generate_var_maps(Node *parent) {
    const_var = allocate_temp_var(parent, data_type);
}

std::string ConstantFloat::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    if (data_type == "float") {
        std::string binaryValue = convertFloatToBinary(value);
        result = "li $15, " + binaryValue + "\n";
        result += store_mapped_variable((Scope *) parent_scope, const_var, "$15");
    }
    return result;
}

Node* ConstantFloat::get_intermediate_variable() {
    return const_var;
}

Assign::Assign(Node *_destination, Node *_source) : destination(_destination), source(_source) {
    this->type = "Assign";
}

void Assign::generate_var_maps(Node *parent) {

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

    //Calculate Rvalue
    result += source->compileToMIPS(parent_scope);
    Node *src_var = source->get_intermediate_variable();
    result += load_mapped_variable((Scope *) parent_scope, src_var, "$14");

    if (destination->type == "Variable") {

        result += store_mapped_variable((Scope *) parent_scope, destination, "$14");

    }else if (destination->type == "UnaryOperator" && destination->subtype == "Dereference"){
        //Load pointer address
        result += load_mapped_variable((Scope *) parent_scope, ((UnaryOperator *) destination)-> in ->get_intermediate_variable(), "$13");

        //Store at pointer address
        result += store_raw_variable((Scope*) parent_scope, "$13", "$14", destination->data_type);
    }
    return result;
};

