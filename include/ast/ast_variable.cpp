#include "ast_variable.hpp"

Variable::Variable(const std::string &_type, const std::string &_name, const bool _declaration) : variable_type(_type), name(_name), declaration(_declaration) {
    this->type = "Variable";
};

std::string *Variable::getName() {
    return &(this->name);
}

std::string *Variable::getVariableType() {
    return &(this->variable_type);
}

void Variable::generate_var_maps(Node *parent) {}