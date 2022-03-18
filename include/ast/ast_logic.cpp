//
// Created by michal on 16. 3. 2022.
//
#include "ast_logic.hpp"

LogicAnd::LogicAnd(Node *L, Node *R) {
    this->type = "LogicAnd";
    this->L = L;
    this->R = R;
}

LogicOr::LogicOr(Node *L, Node *R) {
    this->type = "LogicOr";
    this->L = L;
    this->R = R;
}
LogicNot::LogicNot(Node *_source) {
    this->type = "LogicNot";
    this->source = _source;
}
LogicEQ::LogicEQ(Node *L, Node *R) {
    this->type = "Equal";
    this->L = L;
    this->R = R;
}
LogicNE::LogicNE(Node *L, Node *R) {
    this->type = "NotEqual";
    this->L = L;
    this->R = R;
}
LogicLT::LogicLT(Node *L, Node *R) {
    this->type = "LessThan";
    this->L = L;
    this->R = R;
}
LogicGT::LogicGT(Node *L, Node *R) {
    this->type = "GreaterThan";
    this->L = L;
    this->R = R;
}

LogicGE::LogicGE(Node *L, Node *R) {
    this->type = "GreaterEqual";
    this->L = L;
    this->R = R;
}

LogicLE::LogicLE(Node *L, Node *R) {
    this->type = "LessEqual";
    this->L = L;
    this->R = R;
}

