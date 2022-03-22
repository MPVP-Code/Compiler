//
// Created by michal on 15. 3. 2022.
//

#ifndef AST_LOGIC_HPP
#define AST_LOGIC_HPP
#include "ast_node.hpp"
#include "ast_operator.hpp"

class LogicAnd : public BinaryOperator {
public:
    LogicAnd(Node *_L, Node *_R);

};

class LogicOr : public BinaryOperator {
public:
    LogicOr(Node *_L, Node *_R);

};
class LogicNot : public UnaryOperator {
public:
    LogicNot(Node *_source);

};

class LogicEQ : public BinaryOperator { //Equality operator
public:
    LogicEQ(Node *_L, Node *_R);

};

class LogicNE : public BinaryOperator { // Not equal operator
public:
    LogicNE(Node *_L, Node *_R);

};

class LogicLT : public BinaryOperator { //Less than or equal
public:
    LogicLT(Node *_L, Node *_R);

};

class LogicGT : public BinaryOperator { // Greater than or equal
public:
    LogicGT(Node *_L, Node *_R);

};

class LogicLE : public BinaryOperator { //Less than or equal
public:
    LogicLE(Node *_L, Node *_R);

};

class LogicGE : public BinaryOperator { // Greater than or equal
public:
    LogicGE(Node *_L, Node *_R);

};




#endif
