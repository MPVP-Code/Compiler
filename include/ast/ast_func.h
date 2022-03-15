#ifndef AST_FUNC_H
#define AST_FUNC_H

#include "ast_scope.h"
#include "ast_node.cpp"

class FunctionDeclaration : public Scope
{
public:
    std::vector<Node*> statements;
    std::string return_type;
    std::string name;


    FunctionDeclaration(std::string _return_type, std::string _name, std::vector<Node*> _statements);

    virtual ~FunctionDeclaration();

    std::string* getName();
};

class FunctionCall : public Node {
public:
    std::string function_name;

    FunctionCall(std::string _function_name, std::vector<Node*> arguments);
};

#endif
