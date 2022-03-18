//
// Created by michal on 16. 3. 2022.
//

#include "ast_bitwise.hpp"

BitAnd::BitAnd(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->type = "BitAnd";
}

BitOr::BitOr(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->type = "BitOr";
}

BitXor::BitXor(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->type = "BitXor";
}

BitNot::BitNot(Node *_in) : UnaryOperator(_in){
    this->type = "BitNot";
}

BitASL::BitASL(Node *_L, Node* _R) : BinaryOperator(_L, _R){
    this->subtype = "ASL";
}

BitASR::BitASR(Node *_L, Node* _R) : BinaryOperator(_L, _R){
    this->subtype = "ASR";
}