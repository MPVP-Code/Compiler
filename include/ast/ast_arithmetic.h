#ifndef AST_ARITHMETIC_HPP
#define AST_ARITHMETIC_HPP

#include "ast_node.h"

class Addition : public Node {
public:
    Node *L;
    Node *R;

    Addition(Node *L, Node *R);

    Node* getL();

    Node* getR();

    bool isLInt();

    bool isRInt();

    virtual void generate_var_maps(Node *parent) override;
};

class Subtraction : public Node {
public:
    Node *R;
    Node *L;

    Subtraction(Node *L, Node *R);

    virtual void generate_var_maps(Node *parent) override;
};

class Multiplication : public Node {
public:
    Node *R;
    Node *L;

    Multiplication(Node *L, Node *R);

    virtual void generate_var_maps(Node *parent) override;
};

class Division : public Node {
public:
    Node *R;
    Node *L;

    Division(Node *_L, Node *_R);

    virtual void generate_var_maps(Node *parent) override;
};

#endif
