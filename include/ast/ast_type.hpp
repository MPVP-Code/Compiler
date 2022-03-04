//
// Created by michal on 3. 3. 2022.
//

#ifndef AST_TYPE_H
#define AST_TYPE_H

#include <string>
#include <vector>

#include "ast_node.hpp"

class Variable : Node {
public:
    std::string type;
};

class Integer : Variable{
public:
    int value;
    Integer(){
        this->type = "int";
    }
};

class Struct : Variable{
public:
    std::vector<Variable> members;
};



#endif
