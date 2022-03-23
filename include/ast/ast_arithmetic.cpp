#include "ast_arithmetic.hpp"
#include "ast_node.hpp"
#include "ast_variable.hpp"
#include "ast_operator.hpp"
#include "../ast.hpp"

Addition::Addition(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "Addition";
};

void Addition::generate_var_maps(Node *parent) {
    return;
}

Subtraction::Subtraction(Node *_L, Node *_R): BinaryOperator(_L, _R) {
    this->type = "Subtraction";
};


Multiplication::Multiplication(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->type = "Multiplication";
};


Division::Division(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->type = "Division";
}


Modulo::Modulo(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->type = "Division";
}
