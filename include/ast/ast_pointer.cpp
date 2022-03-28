//
// Created by michal on 27. 3. 2022.
//
#include "ast_pointer.hpp"
#include "ast_stack.hpp"

AddressOf::AddressOf(Node *in) : UnaryOperator(in) {
    subtype = "AddressOf";
}

std::string AddressOf::compileToMIPS(const Node *parent_scope) const {
    std::string out = "#Address of \n";
    Variable* var = (Variable*) in->get_intermediate_variable();
    int offset = resolve_variable_offset(var ->name, (Scope*) parent_scope);
    out += "addi $15, $sp, " + std::to_string(offset) + "\n";
    out += store_mapped_variable((Scope*) parent_scope, temp_variable, "$15") + "\n";
    return out;

}

void AddressOf::generate_var_maps(Node *parent) {
    //Generate maps
    std::cerr << "generating var maps for unary operator"<< std::endl;
    try_replace_variable(this->in, parent);

    //Propagate data types //Adds one pointer to front
    data_type = in -> data_type + "*";

    //Add pointer type if does not exist
    if (resolve_variable_size(data_type, (Scope*)parent) == -1000){
        auto scope = (Scope*) parent;
        auto var = new Variable_type(data_type, "int", 4);
        add_to_global_typemap(var, scope);
    }
    //Allocate variable
    temp_variable = allocate_temp_var(parent, data_type);
}

Dereference::Dereference(Node *in) : UnaryOperator(in) {
    subtype = "Dereference";

}

std::string Dereference::compileToMIPS(const Node *parent_scope) const {
    std::string out = "#Dereference \n";
    out += load_mapped_variable((Scope*) parent_scope, in->get_intermediate_variable(), "$13");
    out += load_raw_variable((Scope*) parent_scope, "$13", "$14", this->temp_variable->data_type);
    out += store_mapped_variable((Scope*) parent_scope, temp_variable, "$14");

    return out;
}

void Dereference::generate_var_maps(Node *parent) {
    //Generate maps
    std::cerr << "generating var maps for unary operator"<< std::endl;
    try_replace_variable(this->in, parent);

    //Cuts one pointer from back
    data_type =  (in -> data_type).substr(0, in->data_type.size()-1);

    if (resolve_variable_size(data_type, (Scope*)parent) == -1000){
        auto scope = (Scope*) parent;
        auto var = new Variable_type(data_type, "int", 4);
        add_to_global_typemap(var, scope);
    }

    temp_variable = allocate_temp_var(parent, data_type);
}
