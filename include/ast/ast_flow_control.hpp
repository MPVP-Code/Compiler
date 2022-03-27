#ifndef AST_TYPE_H
#define AST_TYPE_H

#include "ast_node.hpp"
#include "ast_scope.hpp"
#include <vector>

class While: public Scope {
public:
    Node* condition;
    While(Node* _condition, std::vector<Node*> _statements);

    virtual std::string compileToMIPS(const Node *parent_scope) const override;
};

class DoWhile: public Scope {
public:
    Node* condition;
    DoWhile(Node* _condition, std::vector<Node*> _statements);

    virtual std::string compileToMIPS(const Node *parent_scope) const override;
};

class If: public Scope {
public:
    Node* condition;
    std::vector<Node*>* truestatements;
    std::vector<Node*>* falsestatements;


    If(Node* _condition, std::vector<Node*>* _truestatements, std::vector<Node*>* _falsestatements);

    virtual std::string compileToMIPS(const Node *parent_scope) const override;
    std::string compileStatementsToMIPS(std::vector<Node*>* statements) const;
};

class For: public Scope {
public:
    Node* initialization;
    Node* condition;
    Node* update;

    For(Node* _initialization, Node* _condition, Node* _update, std::vector<Node*> _statements);

    virtual std::string compileToMIPS(const Node *parent_scope) const override;
};

#endif