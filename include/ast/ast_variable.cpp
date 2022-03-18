#include "ast_variable.hpp"
#include "../register_allocator.hpp"

Variable::Variable(const std::string &_type, const std::string &_name, const bool _declaration) : variable_type(_type), name(_name), declaration(_declaration) {
    this->type = "Variable";
};

std::string *Variable::getName() {
    return &(this->name);
}

std::string *Variable::getVariableType() {
    return &(this->variable_type);
}

std::string Variable::compileToMIPS() const {
    int registerIndex = RegisterAllocator::getRegisterNumberForVariable(&(this->name));
    return "li $" + std::to_string(registerIndex) + ", 0x0000";
}

void Variable::generate_var_maps(Node *parent) {}