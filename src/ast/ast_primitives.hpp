#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>

class Variable
        : public Expression {
private:
    std::string name;

public:
    Variable(const std::string &_name) : name(_name) {}

    virtual std::string to_string() const override {
        return "Variable => ( \"" + this->name +  "\" )";
    }
};

class Number
        : public Expression {
private:
    double value;

public:
    Number(double _value) : value(_value) {}

    virtual std::string to_string() const override {
        std::cerr << "error: " << this->value << std::endl;
        return "Number => ( " + std::to_string(this->value) + " )";
    }

};

#endif
