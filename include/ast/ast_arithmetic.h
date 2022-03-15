//
// Created by michal on 9. 3. 2022.
//

#ifndef AST_ARITHMETIC_HPP
#define AST_ARITHMETIC_HPP

#include "ast_node.h"
#include "../register_allocator.h"

class Addition : public Node {
public:
    Node *L;
    Node *R;

    Addition(Node *L, Node *R);

    Node* getL();

    Node* getR();

    bool isLInt();

    bool isRInt();
};

class Subtraction : public Node {
public:
    Node *R;
    Node *L;

    Subtraction(Node *L, Node *R);
};

class Multiplication : public Node {
public:
    Node *R;
    Node *L;

    Multiplication(Node *L, Node *R);

};

class Division : public Node {
public:
    Node *R;
    Node *L;

    Division(Node *_L, Node *_R);

};

#endif
