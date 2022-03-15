#include "ast_arithmetic.h"
#include "ast_node.h"
#include "ast_variable.h"

Addition::Addition(Node *_L, Node *_R): L(_L), R(_R) {
    this->type = "Addition";
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

void Addition::generate_var_maps(Node *parent) {}

Subtraction::Subtraction(Node *_L, Node *_R): L(_L), R(_R) {
    this->type = "Subtraction";
};

void Subtraction::generate_var_maps(Node *parent) {}

Multiplication::Multiplication(Node *_L, Node *_R) : L(_L), R(_R) {
    this->type = "Multiplication";
};

void Multiplication::generate_var_maps(Node *parent) {}

Division::Division(Node *_L, Node *_R) : L(_L), R(_R) {
    this->type = "Division";
}

void Division::generate_var_maps(Node *parent) {}