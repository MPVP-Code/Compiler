#include "ast_syntax.h"

#include <string>

Identifier::Identifier(std::string id) {
    this->type = "Identifier";
    this->identifier = id;
}

