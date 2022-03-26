#include "ast_bitwise.hpp"
#include "ast_scope.hpp"
#include "ast_stack.hpp"

BitAnd::BitAnd(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->type = "BitAnd";
}

std::string BitAnd::compileToMIPS(const Node *parent_scope) const {
    return compileBinaryOperatorToMIPS(parent_scope, "and");
}

BitOr::BitOr(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->type = "BitOr";
}

std::string BitOr::compileToMIPS(const Node *parent_scope) const {
    return compileBinaryOperatorToMIPS(parent_scope, "or");
}

BitXor::BitXor(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->type = "BitXor";
}

std::string BitXor::compileToMIPS(const Node *parent_scope) const {
    return compileBinaryOperatorToMIPS(parent_scope, "xor");
}

BitNot::BitNot(Node *_in) : UnaryOperator(_in){
    this->type = "BitNot";
}

BitASL::BitASL(Node *_L, Node* _R) : BinaryOperator(_L, _R){
    this->subtype = "ASL";
}

std::string BitASL::compileToMIPS(const Node *parent_scope) const {
    return compileBinaryOperatorToMIPS(parent_scope, "sll");
}

BitASR::BitASR(Node *_L, Node* _R) : BinaryOperator(_L, _R){
    this->subtype = "ASR";
}

std::string BitASR::compileToMIPS(const Node *parent_scope) const {
    return compileBinaryOperatorToMIPS(parent_scope, "srav");
}