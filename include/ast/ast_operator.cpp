//
// Created by michal on 18. 3. 2022.
//
#include "ast_operator.hpp"
#include "../ast.hpp"

BinaryOperator::BinaryOperator(Node *_L, Node *_R) {
    this->type = "BinaryOperator";
    this->L = _L;
    this->R = _R;
}

void BinaryOperator::generate_var_maps(Node *parent) {
    //Generate maps left
    try_replace_variable(this->L, parent);

    //Generate maps right
    try_replace_variable(this->R, parent);

    //Propagate types
    data_type = L->data_type;

    //Generate temporary variable
    std::string tmpname = "!tmp" + std::to_string(((Scope*) parent)->tmp_var_counter++);
    this->temp_variable = new Variable(this->data_type, tmpname , true);

    auto scope = (Scope*) parent;
    scope->var_map[tmpname] = this->temp_variable;
}

Node* BinaryOperator::getL() const {
    return L;
};

Node* BinaryOperator::getR() const {
    return R;
};

bool BinaryOperator::isLInt() const {
    return L->get_type().compare("Variable") == 0 && ((Variable *) L)->getVariableType()->compare("int") == 0;
};

bool BinaryOperator::isRInt() const {
    return R->get_type().compare("Variable") == 0 && ((Variable *) R)->getVariableType()->compare("int") == 0;
}


UnaryOperator::UnaryOperator(Node* _in) {
    this->type = "UnaryOperator";
    this->in = _in;
}

void UnaryOperator::generate_var_maps(Node *parent){
    //Generate maps
    try_replace_variable(this->in, parent);

    //Propagate data types
    data_type = in -> data_type;
    std::string tmpname = "!tmp" + std::to_string(((Scope*) parent)->tmp_var_counter++);
    this->temp_variable = new Variable(this->data_type, tmpname , true);

    auto scope = (Scope*) parent;
    scope->var_map[tmpname] = this->temp_variable;
}