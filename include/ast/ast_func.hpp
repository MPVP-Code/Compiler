//
// Created by michal on 4. 3. 2022.
//

#ifndef AST_FUNC_H
#define AST_FUNC_H

#include "ast_node.hpp"
#include "ast_scope.hpp"

class FunctionDeclaration : public Scope
{
public:
    std::vector<Node*> statements;
    std::string return_type;
    std::string name;


    FunctionDeclaration(std::string _return_type, std::string _name, std::vector<Node*> _statements){
        this->statements = _statements;
        this->type = "Function";
        this->name = _name;
        this->return_type = _return_type;
    }

    virtual ~FunctionDeclaration() {}

    virtual std::string get_type(){
        return this->type;
    }

    virtual double compile() const {
        throw std::runtime_error("Compile not implemented.");
    }

    virtual double print() const {
        throw std::runtime_error("Print not implemented.");
    }

    virtual std::string compileToMIPS() const {
        std::string result = this->name + "():\n";

        for (Node *statement : statements) {
            result += statement->compileToMIPS();
        }

        return result;
    }
};

class FunctionCall : public Node {
public:
    std::string function_name;

    FunctionCall(std::string _function_name, std::vector<Node*> arguments){
        this->function_name =  function_name;
        this->branches  =  arguments;

    }
};

#endif
