#ifndef AST_SCOPE_HPP
#define AST_SCOPE_HPP

#include "ast_node.hpp"
#include "ast_variable.hpp"
#include <string>

#include <map>

class Scope : public Node {
public:
    Scope *parent_scope;
    std::map<std::string, Variable *> var_map;

    Scope();

    virtual std::string compileToMIPS() const override;

    virtual void generate_var_maps(Node *parent) override;

    Variable* resolve_variable_scope(std::string name);

    std::vector<Node *> *getBranches();
};

class Global : public Scope {
public:
    Global();

    virtual std::string compileToMIPS() const override;
};

#endif

