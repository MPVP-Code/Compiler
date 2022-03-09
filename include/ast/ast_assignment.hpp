#ifndef AST_ASSIGNMENT_H
#define AST_ASSIGNMENT_H

#include "ast_node.hpp"
#include "ast_type.hpp"

class Assign : Node {
private:
    Variable *destination;
    Node *value;

public:
    Assign(Variable *_destination, Node *_value) : destination(_destination), value(_value) {
        this->type = "Assign";
    }
};

/*class Add : Node {
private:
    Variable *destination;
    Node *value;
};*/

#endif
