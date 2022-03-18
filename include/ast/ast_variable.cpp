#include "ast_variable.hpp"

Variable::Variable(const std::string &_type, const std::string &_name, const bool _declaration) : name(_name), declaration(_declaration) {
    this->type = "Variable";
    this->data_type = _type;
};

std::string *Variable::getName() {
    return &(this->name);
}

std::string *Variable::getVariableType() {
    return &(this->data_type);
}

void Variable::generate_var_maps(Node *parent) {
    return;
}