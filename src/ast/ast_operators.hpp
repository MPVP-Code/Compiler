#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>
#include <cmath>

class AssignmentOperator
        : public Expression {
private:
    Expression* var;
    Expression* number;

public:
    AssignmentOperator(Expression* _var, Expression* _number) : var(_var), number(_number) {}

    virtual ~AssignmentOperator() {
        delete var;
        delete number;
    }

    virtual std::string to_string() const override {
        return "Assignment => ( " + this->var->to_string() + " " + this->number->to_string() + " )";
    }
};

#endif
