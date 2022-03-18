#include "ast_arithmetic.hpp"
#include "ast_node.hpp"
#include "ast_variable.hpp"
#include "ast_operator.hpp"
#include "../ast.hpp"

Addition::Addition(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "Addition";
};

Node* Addition::getL() {
    return L;
};

Node* Addition::getR() {
    return R;
};

bool Addition::isLInt() {
    return L->get_type().compare("Variable") == 0 && ((Variable *) L)->getVariableType()->compare("int") == 0;
};

bool Addition::isRInt() {
    return R->get_type().compare("Variable") == 0 && ((Variable *) R)->getVariableType()->compare("int") == 0;
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
