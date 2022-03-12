#ifndef AST_TYPE_H
#define AST_TYPE_H

#include <string>
#include <vector>

#include "ast_node.hpp"


class Variable : public Node {
public:
    std::string variable_type;
    std::string name;
    bool declaration;

    Variable(const std::string &_type, const std::string &_name, const bool _declaration) : variable_type(_type), name(_name), declaration(_declaration) {
        this->type = "Variable";
    }

    std::string* getName() {
        return &(this->name);
    }
};



#endif
