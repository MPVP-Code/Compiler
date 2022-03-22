#ifndef AST_VARIABLE_H
#define AST_VARIABLE_H

#include <string>
#include <vector>

#include "ast_node.hpp"

class Variable : public Node {
public:
    std::string name;
    bool declaration;

    Variable(const std::string &_type, const std::string &_name, const bool _declaration);

    std::string* getName();

    std::string* getVariableType();

    virtual void generate_var_maps(Node *parent) override;
};

class Variable_type{
public:
    std::string name;
    std::string aliasfor;
    int size;
    Variable_type(){
        
    }
};

#endif