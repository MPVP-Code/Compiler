#ifndef AST_FUNC_HPP
#define AST_FUNC_HPP

#include "ast_scope.hpp"
#include "ast_node.hpp"

#include <vector>

class FunctionDeclaration : public Scope
{
public:
    std::string return_type;
    std::string name;


    FunctionDeclaration(std::string _return_type, std::string _name, std::vector<Node*> _statements);

    virtual ~FunctionDeclaration();

    std::string* getName();

    virtual std::string compileToMIPS() const override;

};

class FunctionCall : public Node {
public:
    std::string function_name;

    FunctionCall(std::string _function_name, std::vector<Node*> arguments);
};

#endif
