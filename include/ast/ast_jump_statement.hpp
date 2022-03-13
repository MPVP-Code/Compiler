#ifndef AST_RETURN_EXPRESSION_H
#define AST_RETURN_EXPRESSION_H

#include "./ast_node.hpp"

class ReturnExpression: public Node {
private:
    Node* expression;
public:
    ReturnExpression(Node* _expression): expression(_expression) {
        this->type = "ReturnExpression";
    }
};

#endif