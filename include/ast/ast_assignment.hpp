#ifndef AST_ASSIGNMENT_H
#define AST_ASSIGNMENT_H

#include "ast_node.hpp"
#include "ast_type.hpp"

class Assign : Node {
private:
    Variable *destination;
    Node *source;

public:
    Assign(Variable *dest, Node *src){
        this->destination = dest;
        this->source = src;
        this->type = "Assign";
    }
};

/*class Declare : Node {

public:
    Variable *destination;
    Node *source;

    Declare(Variable *dest, Node *src){
        this->destination = dest;
        this->source = src;
        this->type = "Assign";
    }
};*/

/*class Add : Node {
private:
    Variable *destination;
    Node *value;
};*/

#endif
