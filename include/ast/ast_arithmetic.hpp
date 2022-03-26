#ifndef AST_ARITHMETIC_HPP
#define AST_ARITHMETIC_HPP

#include "ast_node.hpp"
#include "ast_operator.hpp"
#include "../ast.hpp"

class Addition : public BinaryOperator {
public:
    Addition(Node *_L, Node *_R);
    std::string compileToMIPS(const Node *parent_scope) const;
};

class Subtraction : public BinaryOperator {
public:

    Subtraction(Node *L, Node *R);
    std::string compileToMIPS(const Node *parent_scope) const;

};

class Multiplication : public BinaryOperator {
public:

    Multiplication(Node *L, Node *R);
    std::string compileToMIPS(const Node *parent_scope) const;

};

class Division : public BinaryOperator {
public:

    Division(Node *_L, Node *_R);
    std::string compileToMIPS(const Node *parent_scope) const;

};
class Modulo : public BinaryOperator {
public:

    Modulo(Node *_L, Node *_R);
    std::string compileToMIPS(const Node *parent_scope) const;

};

class UnaryMinus : public UnaryOperator {
public:

    UnaryMinus(Node *in);
    std::string compileToMIPS(const Node *parent_scope) const;

};

#endif
