#ifndef AST_ASSIGNMENT_H
#define AST_ASSIGNMENT_H

#include "ast_variable.hpp"
#include "ast_scope.hpp"
#include "ast_node.hpp"
#include "../register_allocator.hpp"
#include <string>


class Constant : public Node {
private:
    int value;

public:
    Constant(int _value);

    int getValue();
};

class Assign : public Node {
private:
    Variable *destination;
    Node *source;

public:
    Assign(Variable *_destination, Node *_source);

    virtual std::string compileToMIPS() const override;

    virtual void generate_var_maps(Node *parent) override;
};

#endif
