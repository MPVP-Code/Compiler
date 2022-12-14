#ifndef AST_ASSIGNMENT_H
#define AST_ASSIGNMENT_H

#include "ast_variable.hpp"
#include "ast_scope.hpp"
#include "ast_node.hpp"
#include <string>


class Constant : public Node {
public:
    Variable* const_var;

    int value;

    Constant(int _value);

    int getValue();

    virtual void generate_var_maps(Node *parent) override;

    std::string compileToMIPS(const Node *parent_scope) const override;

    virtual Node* get_intermediate_variable() override;

};

class StringLiteral : public Constant {
public:

    std::string str_value;

    StringLiteral(int value, std::string _in);

    virtual void generate_var_maps(Node *parent) override;

    std::string compileToMIPS(const Node *parent_scope) const override;

};

class ConstantFloat : public Node {
private:
    float value;
    Variable* const_var;

public:
    ConstantFloat(float _value);

    float getValue();

    Variable* getConstVar();

    virtual void generate_var_maps(Node *parent) override;

    std::string compileToMIPS(const Node *parent_scope) const override;

    virtual Node* get_intermediate_variable() override;

};

class Assign : public Node {
private:
    Node *destination;
    Node *source;

public:
    Assign(Node *_destination, Node *_source);

    std::string compileToMIPS(const Node *parent_scope) const override;

    void generate_var_maps(Node *parent) override;
};

#endif
