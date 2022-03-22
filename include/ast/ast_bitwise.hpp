////
//// Created by michal on 15. 3. 2022.
////

#ifndef AST_BITWISE_HPP
#define AST_BITWISE_HPP

#include "ast_node.hpp"
#include "ast_operator.hpp"

class BitAnd : public BinaryOperator {
public:
    BitAnd(Node *_L, Node *_R);

};

class BitOr : public BinaryOperator {
public:
    BitOr(Node *_L, Node *_R);

};

class BitXor : public BinaryOperator {
public:
    BitXor(Node *_L, Node *_R);

};

class BitNot : public UnaryOperator {
public:
    BitNot(Node *_in);
};

class BitASL : public BinaryOperator {
public:
    BitASL(Node *_L, Node *_R); //Value, shift
};

class BitASR : public BinaryOperator {
public:
    BitASR(Node *_L, Node *_R); //Value, shift
};

#endif

