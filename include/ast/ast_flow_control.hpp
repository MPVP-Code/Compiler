//
// Created by michal on 3. 3. 2022.
//

#ifndef AST_TYPE_H
#define AST_TYPE_H

#include "ast_node.hpp"
#include "ast_scope.hpp"
#include <vector>

class While: public Scope {
public:
    Node* condition;
    While(Node* _condition, std::vector<Node*> _statements);

    virtual std::string compileToMIPS() const override;
};

class If: public Scope {
public:
    Node* condition;
    std::vector<Node*>* truestatements;
    std::vector<Node*>* falsestatements;


    If(Node* _condition, std::vector<Node*>* _truestatements, std::vector<Node*>* _falsestatements);

    virtual std::string compileToMIPS() const override;
    std::string compileStatementsToMIPS(std::vector<Node*>* statements) const;
};

#endif