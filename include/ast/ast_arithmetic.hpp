//
// Created by michal on 9. 3. 2022.
//

#ifndef AST_ARITHMETIC_HPP
#define AST_ARITHMETIC_HPP

#include "../ast.hpp"

class Addition : public Node {
public:
    Node *R;
    Node *L;

    Addition(Node *L, Node *R) {
        this->type = "Addition";
        this->L = L;
        this->R = R;
    }

};

class Subtraction : public Node {
public:
    Node *R;
    Node *L;

    Subtraction(Node *L, Node *R) {
        this->type = "Subtraction";
        this->L = L;
        this->R = R;
    }

};

class Multiplication : public Node {
public:
    Node *R;
    Node *L;

    Multiplication(Node *_L, Node *_R) : L(_L), R(_R) {
        this->type = "Multiplication";
    }

};

class Division : public Node {
public:
    Node *R;
    Node *L;

    Division(Node *_L, Node *_R) : L(_L), R(_R) {
        this->type = "Division";
    }

};

#endif
