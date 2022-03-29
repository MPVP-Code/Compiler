#ifndef AST_SCOPE_HPP
#define AST_SCOPE_HPP

#include "ast_node.hpp"
#include "ast_variable.hpp"
#include <string>

#include <map>

class Scope : public Node {
public:
    std::vector<Node *> statements;  //New instead of branches
    bool array_init_flag;
    Scope *parent_scope;
    std::map<std::string, Variable*> var_map;
    std::map<std::string, Variable_type*> type_map;
    int stack_frame_size;
    int tmp_var_counter;
    bool l_dereference_flag;
    Scope();

    virtual std::string compileToMIPS(const Node *parent_scope) const override;

    virtual void generate_var_maps(Node *parent) override;

    std::vector<Node *> *getBranches();
};
class Global : public Scope {
private:
    static int logicAndCount;
    static int logicOrCount;
    static int forCount;
    static int ifCount;
    static int whileCount;
    static int switchCount;
public:
    std::map<std::string, Node*> declaration_map;

    Global();

    static int getIdForWhile();

    static int getIdForForLoop();

    static int getIdForIf();

    static int getIdForLogicAnd();

    static int getIdForLogicOr();

    static int getIdForSwitch();

    virtual std::string compileToMIPS(const Node *parent_scope) const override;
};

class CompoundStatement : public Scope{
public:
    CompoundStatement(std::vector<Node*> _statements);
    virtual std::string compileToMIPS(const Node *parent_scope) const override;
};

#endif

