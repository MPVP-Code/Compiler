#ifndef AST_TYPE_H
#define AST_TYPE_H

#include <string>
#include <vector>

#include "ast_node.hpp"

class TypeSpecifier : DeclarationSpecifiers {
protected:
    const std::string* name;
public:
    TypeSpecifier(const std::string* _name): name(_name) {}

    virtual std::string to_string() const {
        return "TypeSpecifier => (" + *this->name + ")";
    }
};

class Variable : Node {
protected:
    std::string type;
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

class Struct : Variable {
public:
    std::vector<Variable> members;
};


#endif
