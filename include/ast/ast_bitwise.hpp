#ifndef AST_BITWISE_HPP
#define AST_BITWISE_HPP

#include "ast_node.hpp"
#include "ast_operator.hpp"

class BitAnd : public BinaryOperator {
public:
    BitAnd(Node *_L, Node *_R);

    std::string compileToMIPS(const Node *parent_scope) const;
};

class BitOr : public BinaryOperator {
public:
    BitOr(Node *_L, Node *_R);

    std::string compileToMIPS(const Node *parent_scope) const;
};

class BitXor : public BinaryOperator {
public:
    BitXor(Node *_L, Node *_R);

    std::string compileToMIPS(const Node *parent_scope) const;
};

class BitNot : public UnaryOperator {
public:
    BitNot(Node *_in);

    std::string compileToMIPS(const Node *parent_scope) const;
};

class BitASL : public BinaryOperator {
public:
    BitASL(Node *_L, Node *_R); //Value, shift

    std::string compileToMIPS(const Node *parent_scope) const;
};

class BitASR : public BinaryOperator {
public:
    BitASR(Node *_L, Node *_R); //Value, shift

    std::string compileToMIPS(const Node *parent_scope) const;
};

#endif

