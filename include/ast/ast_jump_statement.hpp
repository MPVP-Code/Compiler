#ifndef AST_RETURN_EXPRESSION_H
#define AST_RETURN_EXPRESSION_H

#include "./ast_node.hpp"

class Return: public Node {
private:
    Node* expression;
public:
    Return(Node* _expression): expression(_expression) {
        this->type = "ReturnExpression";
    }
};

#endif