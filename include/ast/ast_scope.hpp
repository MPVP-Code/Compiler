//
// Created by michal on 4. 3. 2022.
//

#ifndef AST_SCOPE_HPP
#define AST_SCOPE_HPP

#include "ast_node.hpp"
#include "ast_type.hpp"

#include <map>
#include <string>
#include <vector>

class Scope : public Node
{
public:
    //Inherits branches & type
    std::vector<std::shared_ptr<Scope>> parent_scope;
    //std::map<std::string,Variable> var_map;

    Scope(){
        this->type = "Scope";
    }

    //Has gettype

    virtual double compile() const override{
        throw std::runtime_error("Scope compile not implemented.");
    }

    virtual double print() const override{
        throw std::runtime_error("Scope compile print not implemented.");
    }
};

class Global : public Scope
{
public:
    //Inherits branches & type

    Global(){
        this->type = "Global";
    }

    //Has gettype

    virtual double compile() const override{
        throw std::runtime_error("Global compile not implemented.");
    }

    virtual double print() const override{
        throw std::runtime_error("Global print not implemented.");
    }
};

#endif


