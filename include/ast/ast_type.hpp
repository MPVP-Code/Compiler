#ifndef AST_TYPE_H
#define AST_TYPE_H

#include <string>
#include <vector>

#include "ast_node.hpp"


class Variable : Node {
protected:
    std::string type;
    std::string name;

public:
    Variable(const std::string &_type, const std::string &_name) : type(_type), name(_name) {}
};


//class Struct : Variable {
//public:
//    std::vector<Variable> members;
//};


#endif
