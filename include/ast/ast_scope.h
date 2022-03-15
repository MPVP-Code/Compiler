#ifndef AST_SCOPE_HPP
#define AST_SCOPE_HPP

#include "ast_node.h"
#include <string>

class Identifiera : public Node {
public:
    std::string identifier;

    Identifiera(std::string id);
};
#endif

