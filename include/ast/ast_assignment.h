#ifndef AST_ASSIGNMENT_H
#define AST_ASSIGNMENT_H

#include "ast_variable.h"
#include "ast_scope.h"
#include "ast_node.h"
#include "../register_allocator.h"
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
