//
// Created by michal on 9. 3. 2022.
//

#ifndef AST_ARITHMETIC_HPP
#define AST_ARITHMETIC_HPP

#include "ast_node.hpp"

class Addition : public Node
{
public:

    Addition(std::shared_ptr<Node> L, std::shared_ptr<Node> R){
        this->type = "Addition";
        this->branches.push_back(L);
        this->branches.push_back(L);

    }

};

class Subtraction : public Node
{
public:

    Subtraction(std::shared_ptr<Node> L, std::shared_ptr<Node> R){
        this->type = "Subtraction";
        this->branches.push_back(L);
        this->branches.push_back(L);

    }

};

class Multiplication : public Node
{
public:

    Multiplication(std::shared_ptr<Node> L, std::shared_ptr<Node> R){
        this->type = "Addition";
        this->branches.push_back(L);
        this->branches.push_back(L);

    }

};

class Division : public Node
{
public:

    Division(std::shared_ptr<Node> L, std::shared_ptr<Node> R){
        this->type = "Division";
        this->branches.push_back(L);
        this->branches.push_back(L);

    }

};

#endif
