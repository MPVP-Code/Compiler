#ifndef AST_SYNTAX_HPP
#define AST_SYNTAX_HPP

#include "ast_node.h"
#include <string>

class Identifier : public Node {
public:
    std::string identifier;

    Identifier(std::string id);

    virtual void generate_var_maps(Node *parent) override;
};
#endif
