//
// Created by michal on 16. 3. 2022.
//
#include "ast_logic.hpp"

LogicAnd::LogicAnd(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "LogicAnd";
}

LogicOr::LogicOr(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "LogicOr";
}
LogicNot::LogicNot(Node *_source) : UnaryOperator(_source){
    this->subtype = "LogicNot";
}
LogicEQ::LogicEQ(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "Equal";
}
LogicNE::LogicNE(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "NotEqual";
}
LogicLT::LogicLT(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "LessThan";
}
LogicGT::LogicGT(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "GreaterThan";
}

LogicGE::LogicGE(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "GreaterEqual";
}

LogicLE::LogicLE(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "LessEqual";
}

