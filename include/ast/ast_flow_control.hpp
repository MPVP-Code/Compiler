#ifndef AST_TYPE_H
#define AST_TYPE_H

#include "ast_node.hpp"
#include "ast_scope.hpp"
#include <vector>

class While: public Scope {
private:
    std::string whileEndLabel;
    std::string whileStartLabel;
    std::string whileConditionLabel;

public:
    Node* condition;
    While(Node* _condition, std::vector<Node*> _statements);

    virtual std::string compileToMIPS(const Node *parent_scope) const override;

    std::string getEndLabel();

    std::string getConditionLabel();
};

class DoWhile: public Scope {
private:
    std::string doWhileEndLabel;
    std::string doWhileStartLabel;
    std::string doWhileConditionLabel;

public:
    Node* condition;
    DoWhile(Node* _condition, std::vector<Node*> _statements);

    virtual std::string compileToMIPS(const Node *parent_scope) const override;

    std::string getEndLabel();

    std::string getConditionLabel();
};

class If: public Scope {
public:
    Node* condition;
    std::vector<Node*>* truestatements;
    std::vector<Node*>* falsestatements;


    If(Node* _condition, std::vector<Node*>* _truestatements, std::vector<Node*>* _falsestatements);

    virtual std::string compileToMIPS(const Node *parent_scope) const override;
    std::string compileStatementsToMIPS(std::vector<Node*>* statements, const Node *parent_scope) const;
};

class For: public Scope {
private:
    std::string forStatementsLabel;
    std::string forEndLabel;
    std::string forConditionLabel;
public:
    Node* initialization;
    Node* condition;
    Node* update;

    For(Node* _initialization, Node* _condition, Node* _update, std::vector<Node*> _statements);

    virtual std::string compileToMIPS(const Node *parent_scope) const override;

    std::string getEndLabel();

    std::string getConditionLabel();
};

class Switch: public Node {
private:
    std::vector<Node*> statements;
    Node* condition;

public:
    Switch(Node* _condition, std::vector<Node*> _statements);

    virtual void generate_var_maps(Node *parent) override;

    virtual std::string compileToMIPS(const Node *parent_scope) const override;
};

class Case: public Node {
private:
    Node *constant;
    std::vector<Node*> statements;
public:
    Case(Node* _constant, std::vector<Node*> _statements);

    virtual void generate_var_maps(Node *parent) override;

    std::string compileCaseToMIPS(const Node *parent_scope, Variable* condition, std::string caseEndLabel) const;

    virtual std::string compileToMIPS(const Node *parent_scope) const override;
};

class DefaultCase: public Node {
private:
    std::vector<Node*> statements;
public:
    DefaultCase(std::vector<Node*> statements);

    virtual void generate_var_maps(Node *parent) override;

    virtual std::string compileToMIPS(const Node *parent_scope) const override;
};

class Break: public Node {
public:
    Break();

    virtual void generate_var_maps(Node *parent) override;

    virtual std::string compileToMIPS(const Node *parent_scope) const override;
};

class Continue: public Node {
public:
    Continue();

    virtual void generate_var_maps(Node *parent) override;

    virtual std::string compileToMIPS(const Node *parent_scope) const override;
};

#endif