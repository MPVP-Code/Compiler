#include "ast_syntax.hpp"

#include <string>

Identifier::Identifier(std::string id) {
    this->type = "Identifier";
    this->pointer = "None";
    this->identifier = id;
}

SizeOf::SizeOf(Node *in) : UnaryOperator(in) {
    this->subtype = "SizeOf";
}

