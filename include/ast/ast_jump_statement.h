#ifndef AST_RETURN_EXPRESSION_H
#define AST_RETURN_EXPRESSION_H

#include "ast_node.h"

class Return: public Node {
private:
    Node* expression;
public:
    Return(Node* _expression);

    virtual std::string compileToMIPS() const override;
};

#endif