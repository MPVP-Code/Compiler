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
    if (L->type == "Variable") {
        auto temp = (Variable *) L;
        if (temp->declaration) {
            ((Scope *) parent)->var_map[temp->name] = temp;
        }
    } else {
        L->generate_var_maps(parent);
    }

    //Generate maps right
    if (R->type == "Variable") {
        auto temp = (Variable *) R;
        if (temp->declaration) {
            ((Scope *) parent)->var_map[temp->name] = temp;
        }
    } else {
        R->generate_var_maps(parent);

    }

    //Propagate types
    data_type = L->data_type;
}
UnaryOperator::UnaryOperator(Node* _in) {
    this->type = "UnaryOperator";
    this->in = _in;
}

void UnaryOperator::generate_var_maps(Node *parent){
    //Generate maps
    if (in->type == "Variable") {
        auto temp = (Variable *) in;
        if (temp->declaration) {
            ((Scope *) parent)->var_map[temp->name] = temp;
        }
    } else {
        in->generate_var_maps(parent);

    }

    //Propagate data types
    data_type = in -> data_type;
}