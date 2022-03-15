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
public:
    While(Node* _condition, std::vector<Node*>* _statements): condition(_condition) {
        this->type = "While";
        this->branches = *_statements;
    }
};

class If: public Scope {
private:
    Node* condition;
    std::vector<Node*>* truestatements;
    std::vector<Node*>* falsestatements;
public:
    If(Node* _condition, std::vector<Node*>* _statements): condition(_condition) {
        this->type = "If";
        this->branches = *_statements;
    }
};

#endif