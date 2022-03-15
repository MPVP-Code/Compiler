#ifndef AST_FUNC_H
#define AST_FUNC_H

#include "ast_func.h"
#include "ast_scope.h"
#include "ast_node.cpp"

//Scope forward declarations


class FunctionDeclaration : public Scope
{
public:
    std::vector<Node*> statements;
    std::string return_type;
    std::string name;


    FunctionDeclaration(std::string _return_type, std::string _name, std::vector<Node*> _statements){
        this->statements = _statements;

        this->name = _name;
        this->return_type = _return_type;

        //Type specification
        this->type = "Scope";
        this->subtype = "Function";
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
        std::string result = this->name + ":\n.set noreorder\n";

        for (Node *statement : statements) {
            result += statement->compileToMIPS() + "\n";
        }

        result += "jr $31\nnop";
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
