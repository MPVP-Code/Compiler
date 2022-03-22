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
}