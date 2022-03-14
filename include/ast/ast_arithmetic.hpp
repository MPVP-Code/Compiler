//
// Created by michal on 9. 3. 2022.
//

#ifndef AST_ARITHMETIC_HPP
#define AST_ARITHMETIC_HPP

#include "../ast.hpp"
#include "../register_allocator.h"

class Addition : public Node {
public:
    Node *L;
    Node *R;

    Addition(Node *L, Node *R) {
        this->type = "Addition";
        this->L = L;
        this->R = R;
    }

    Node* getL() {
        return L;
    }

    Node* getR() {
        return R;
    }

    bool isLInt() {
        return L->get_type().compare("Variable") == 0 && ((Variable *) L)->getVariableType()->compare("int") == 0;
    }

    bool isRInt() {
        return R->get_type().compare("Variable") == 0 && ((Variable *) R)->getVariableType()->compare("int") == 0;
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

    Multiplication(Node *L, Node *R) {
        this->type = "Multiplication";
        this->L = L;
        this->R = R;
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
