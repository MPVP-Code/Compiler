#ifndef AST_VARIABLE_H
#define AST_VARIABLE_H

#include <string>
#include <vector>

#include "ast_node.cpp"


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

    std::string* getVariableType() {
        return &(this->variable_type);
    }

};



#endif
