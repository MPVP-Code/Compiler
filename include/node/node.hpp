//
// Created by michal on 3. 3. 2022.
//
#ifndef ast_node_hpp
#define ast_node_hpp

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

    virtual ~Node() {}

    virtual std::string type(){
        return this->type;
    }

    virtual double compile() const {
        throw std::runtime_error("Not implemented.");
    }
};

#endif
