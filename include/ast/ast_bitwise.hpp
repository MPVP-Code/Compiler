//
// Created by michal on 15. 3. 2022.
//

#ifndef AST_BITWISE_HPP
#define AST_BITWISE_HPP

#include "ast_node.hpp"
class BitAnd : public Node {
public:
    Node *R;
    Node *L;

    BitAnd(Node *L, Node *R) {
        this->type = "Subtraction";
        this->L = L;
        this->R = R;
    }

};

class BitOr : public Node {
public:
    Node *R;
    Node *L;

    BitOr(Node *L, Node *R) {
        this->type = "Subtraction";
        this->L = L;
        this->R = R;
    }

};

class BitXor : public Node {
public:
    Node *R;
    Node *L;

    BitXor(Node *L, Node *R) {
        this->type = "Subtraction";
        this->L = L;
        this->R = R;
    }

};

class BitNot : public Node {
public:
    Node *in;

    BitNot(Node *_in) {
        this->type = "Subtraction";
        this->in = _in;
    }
};

#endif

