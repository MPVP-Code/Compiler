#include "ast_stack.hpp"
#include "ast_variable.hpp"

Variable::Variable(const std::string &_type, const std::string &_name, const bool _declaration) : name(_name), declaration(_declaration) {
    this->type = "Variable";
    this->data_type = _type;
    this->array_size = -1;
};

std::string *Variable::getName() {
    return &(this->name);
}

std::string *Variable::getVariableType() {
    return &(this->data_type);
}

std::string Variable::compileToMIPS(const Node *parent_scope) const {
    std::string out = "";
    if (this->array_size >0 && ((Scope*) parent_scope) -> array_init_flag){
        out += "#Local array ptr init\n";
        out += "addiu $14, $sp, "+ std::to_string(this->offset + 4) + "\n";
        out += store_mapped_variable((Scope*) parent_scope, this, "$14");
    }
    return  out;
}

void Variable::generate_var_maps(Node *parent) {
    return;
}

Node *Variable::get_intermediate_variable() {
    return this;
}

Variable_type::Variable_type(std::string _name, std::string alias, int _size): name(_name), size(_size), aliasof(alias){}