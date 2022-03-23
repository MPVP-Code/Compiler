#ifndef AST_SCOPE_HPP
#define AST_SCOPE_HPP

#include "ast_node.hpp"
#include "ast_variable.hpp"
#include <string>

#include <map>

class Scope : public Node {
public:
    std::vector<Node *> statements;  //New instead of branches

    Scope *parent_scope;
    std::map<std::string, Variable*> var_map;
    std::map<std::string, Variable_type*> type_map;
    int stack_frame_size;

    Scope();

    virtual std::string compileToMIPS() const override;

    virtual void generate_var_maps(Node *parent) override;

    Variable* resolve_variable_scope(std::string name);

    std::vector<Node *> *getBranches();
};

class Global : public Scope {
private:
    static int whileCount;
    static int ifCount;

public:
    Global();

    static int getIdForWhile();

    static int getIdForIf();

    virtual std::string compileToMIPS() const override;
};

#endif

