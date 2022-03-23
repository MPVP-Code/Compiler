#ifndef AST_ARITHMETIC_HPP
#define AST_ARITHMETIC_HPP

#include "ast_node.hpp"
#include "ast_operator.hpp"
#include "../ast.hpp"

class Addition : public BinaryOperator {
public:
    Addition(Node *_L, Node *_R);

    virtual void generate_var_maps(Node *parent) override;

};

class Subtraction : public BinaryOperator {
public:

    Subtraction(Node *L, Node *R);

};

class Multiplication : public BinaryOperator {
public:

    Multiplication(Node *L, Node *R);

};

class Division : public BinaryOperator {
public:

    Division(Node *_L, Node *_R);

};
class Modulo : public BinaryOperator {
public:

    Modulo(Node *_L, Node *_R);

};

#endif
