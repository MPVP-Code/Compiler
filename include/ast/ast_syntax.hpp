#ifndef AST_SYNTAX_HPP
#define AST_SYNTAX_HPP

#include "ast_node.hpp"
#include "ast_operator.hpp"
#include <string>

class Identifier : public Node {
public:
    std::string identifier;

    Identifier(std::string id);

};

class SizeOf : public UnaryOperator {
public:

    SizeOf(Node *in);
};
#endif
