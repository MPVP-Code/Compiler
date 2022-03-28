#include "ast_syntax.hpp"

#include <string>

SizeOf::SizeOf(Node *in) : UnaryOperator(in) {
    this->subtype = "SizeOf";
}

