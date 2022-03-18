//
// Created by michal on 15. 3. 2022.
//

#ifndef AST_LOGIC_HPP
#define AST_LOGIC_HPP
#include "ast_node.hpp"

class LogicAnd : public Node {
public:
    Node *R;
    Node *L;

    LogicAnd(Node *L, Node *R);

};

class LogicOr : public Node {
public:
    Node *R;
    Node *L;

    LogicOr(Node *L, Node *R);

};
class LogicNot : public Node {
public:
    Node *R;
    Node *source;

    LogicNot(Node *_source);

};

class LogicEQ : public Node { //Equality operator
public:
    Node *R;
    Node *L;

    LogicEQ(Node *L, Node *R);

};

class LogicNE : public Node { // Not equal operator
public:
    Node *R;
    Node *L;

    LogicNE(Node *L, Node *R);

};

class LogicLT : public Node { //Less than or equal
public:
    Node *R;
    Node *L;

    LogicLT(Node *L, Node *R);

};

class LogicGT : public Node { // Greater than or equal
public:
    Node *R;
    Node *L;

    LogicGT(Node *L, Node *R);

};

class LogicLE : public Node { //Less than or equal
public:
    Node *R;
    Node *L;

    LogicLE(Node *L, Node *R);

};

class LogicGE : public Node { // Greater than or equal
public:
    Node *R;
    Node *L;

    LogicGE(Node *L, Node *R);

};




#endif
