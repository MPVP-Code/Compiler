#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <string>
#include <iostream>
#include <map>

#include <memory>

class Expression;

class Expression {
public:
    virtual ~Expression() {}

    virtual std::string to_string() const {
        throw std::runtime_error("Not implemented.");
    };
};


#endif
