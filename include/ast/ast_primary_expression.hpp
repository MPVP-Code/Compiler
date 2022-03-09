#ifndef AST_PRIMARY_EXPRESSION_H
#define AST_PRIMARY_EXPRESSION_H

#include <string>
#include "ast_postfix_expression.hpp"


class PrimaryExpression: PostfixExpression {

};

class Constant: PrimaryExpression {
private:
    double value;
public:
    Constant(double _value): value(_value) {}

    virtual std::string to_string() const {
        return "Constant => (" + std::to_string(this->value) + ")";
    }
};

#endif
