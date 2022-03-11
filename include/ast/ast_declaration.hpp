#ifndef AST_DECLARATION_H
#define AST_DECLARATION_H


#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "ast_node.hpp"

class Declarator : public Node {
public:
    std::string *name;

    Declarator(std::string *_name) {
        this->name = _name;
        this->type = "declarator";
    }
};

class Identifier : public Node {
private:
    const std::string *identifier;
public:
    Identifier(const std::string *_identifier) : identifier(_identifier) {}

    virtual std::string to_string() const {
        return "Identifier => (" + *this->identifier + ")";
    }
};

#endif
