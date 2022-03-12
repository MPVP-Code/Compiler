//
// Created by michal on 3. 3. 2022.
//
#ifndef AST_NODE_H
#define AST_NODE_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>


class Node {
public:
    std::vector<Node*> branches;
    std::vector<int> allocated_branch_reg;
    std::string type;
    std::string data_type;

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

    void virtual generate_var_maps(){
        std::cout<<"gen varmaps not overridden\n";
    }
};

#endif
