//
// Created by michal on 3. 3. 2022.
//
#ifndef AST_NODE_H
#define AST_NODE_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "../ast.hpp"

//Forward declaration
class Scope;

class Node {
public:
    std::vector<Node*> branches;
    std::string data_type;

    //Node disambiguation for pointer casting
    std::string type;
    std::string subtype;
    std::string subsubtype;

    Node() {
        this->type = "Node";
    }

    virtual std::string get_type() {
        return this->type;
    }

    virtual double compile() const {
        throw std::runtime_error( this->type + "compile not implemented.");
    }

    virtual double print() const {
        throw std::runtime_error(  this->type + " print not implemented.");
    }

    virtual std::string to_string() const {
        throw std::runtime_error("Node print not implemented.");
    }

    virtual std::string compileToMIPS() const {
        throw std::runtime_error(  this->type + " compileToMIPS not implemented.");
    }

    virtual void generate_var_maps(Scope* parent){
        std::cout<<"gen varmaps not overridden\n";
    }
};




#endif
