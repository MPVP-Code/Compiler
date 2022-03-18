#include "ast_syntax.hpp"

#include <string>

Identifier::Identifier(std::string id) {
    this->type = "Identifier";
    this->identifier = id;
}

