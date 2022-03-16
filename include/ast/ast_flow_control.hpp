//
// Created by michal on 3. 3. 2022.
//

#ifndef AST_TYPE_H
#define AST_TYPE_H

#include "ast_node.hpp"
#include "ast_scope.hpp"
#include <vector>

class While: public Scope {
private:
    Node* condition;
    std::vector<Node*>* statements;
public:
    While(Node* _condition, std::vector<Node*>* _statements);
};

class If: public Scope {
private:
    Node* condition;
    std::vector<Node*>* truestatements;
    std::vector<Node*>* falsestatements;
public:
    If(Node* _condition, std::vector<Node*>* _truestatements, std::vector<Node*>* _falsestatements);
};

#endif