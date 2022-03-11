#ifndef AST_TYPE_H
#define AST_TYPE_H

#include <string>
#include <vector>

#include "ast_node.hpp"


class Variable : Node {
protected:
    std::string type;
    std::string name;
    int value;

public:
    Variable(const std::string &_type, const std::string &_name, int _value) : type(_type), name(_name), value(_value) {}
};


//class Struct : Variable {
//public:
//    std::vector<Variable> members;
//};


#endif
