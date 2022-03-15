#ifndef AST_NODE_H
#define AST_NODE_H

//#include "ast_scope.h"

#include <memory>
#include <vector>
#include <string>
#include <iostream>

class Node {
public:
    std::vector<Node *> branches;
    std::string data_type;

    //Node disambiguation for pointer casting
    std::string type;
    std::string subtype;
    std::string subsubtype;

    Node();

    /*virtual std::string get_type();

    virtual double compile() const;

    virtual double print() const;

    virtual std::string to_string() const;

    virtual std::string compileToMIPS() const;

    void generate_var_maps(Scope *parent); */
};


#endif
