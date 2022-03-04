//
// Created by michal on 4. 3. 2022.
//

#ifndef AST_FUNC_H
#define AST_FUNC_H

#include "ast_node.hpp"

class Function : public Node
{
public:
    std::vector<std::shared_ptr<Node>> parent_scope;


    Function(){
        this->type = "Node";
    }

    virtual ~Function() {}

    virtual std::string get_type(){
        return this->type;
    }

    virtual double compile() const {
        throw std::runtime_error("Compile not implemented.");
    }

    virtual double print() const {
        throw std::runtime_error("Print not implemented.");
    }
};

#endif AST_FUNC_H
