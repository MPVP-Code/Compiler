#ifndef AST_TYPE_H
#define AST_TYPE_H

#include <string>
#include <vector>

#include "ast_node.hpp"

class Type {
    public:
        std::string identifier;
        int size;
        Type(std::string _identifier, int _size){
            this->identifier = _identifier;
            this->size = _size;
        }
};

class Variable : Node {
protected:
    Type* type;
    std::string name;

public:
    Variable(const std::string &_type, const std::string &_name) : type(_type), name(_name) {}
};

class Integer : Variable {
private:
    int value;

public:
    Integer(const std::string &_name, int _value) : Variable("int", _name), value(_value) {}
};

//class Struct : Variable {
//public:
//    std::vector<Variable> members;
//};


#endif
