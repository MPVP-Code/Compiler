#include "ast_variable.hpp"
#include "../register_allocator.hpp"

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

std::string Variable::compileToMIPS() const {
    int registerIndex = RegisterAllocator::getRegisterNumberForVariable(&(this->name));
    return "li $" + std::to_string(registerIndex) + ", 0x0000";
}

void Variable::generate_var_maps(Node *parent) {
    return;
}

Variable_type::Variable_type(std::string _name, std::string alias, int _size): name(_name), size(_size), aliasof(alias){}