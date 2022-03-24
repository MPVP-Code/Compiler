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
    std::vector<Variable*>* arguments;


    FunctionDeclaration();

    virtual ~FunctionDeclaration();

    std::string* getName();

    virtual std::string compileToMIPS(const Node *parent_scope) const override;

};

class FunctionCall : public Node {
public:
    std::string function_name;
    std::vector<Node*>* arguments;

    FunctionCall(std::string _function_name, std::vector<Node*>* arguments);

    void generate_var_maps(Node *parent) override;
};

#endif
