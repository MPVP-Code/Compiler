#ifndef AST_SYNTAX_HPP
#define AST_SYNTAX_HPP

#include "ast_node.hpp"
#include <string>

class Identifier : public Node {
public:
    std::string identifier;

    Identifier(std::string id);

};
#endif
