//
// Created by michal on 16. 3. 2022.
//

#include "ast_bitwise.hpp"

BitAnd::BitAnd(Node *L, Node *R) {
    this->type = "Subtraction";
    this->L = L;
    this->R = R;
}

BitOr::BitOr(Node *L, Node *R) {
    this->type = "Subtraction";
    this->L = L;
    this->R = R;
}

BitXor::BitXor(Node *L, Node *R) {
    this->type = "Subtraction";
    this->L = L;
    this->R = R;
}

BitNot::BitNot(Node *_in) {
    this->type = "Subtraction";
    this->in = _in;
}