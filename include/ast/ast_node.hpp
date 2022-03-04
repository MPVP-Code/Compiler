//
// Created by michal on 3. 3. 2022.
//
#ifndef AST_NODE_H
#define AST_NODE_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>


class Node
{
public:
    std::vector<std::shared_ptr<Node>> branches;
    std::string type;

    Node(){
        this->type = "Node";
    }

    virtual std::string get_type(){
        return this->type;
    }

    virtual double compile() const {
        throw std::runtime_error("Node compile not implemented.");
    }

    virtual double print() const {
        throw std::runtime_error("Node print not implemented.");
    }
};

#endif
