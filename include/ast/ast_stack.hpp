//
// Created by michal on 22. 3. 2022.
//

#ifndef AST_STACK_HPP
#define AST_STACK_HPP

#include "ast_scope.hpp"
#include "ast_func.hpp"

typedef union {
    float f;
    struct {
        unsigned int mantisa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } parts;
} float_cast;

std::string load_mapped_variable(const Scope* scope, const Node* var, std::string reg_name);
std::string load_mapped_variable_with_offset(const Scope* scope, const Node* _var, std::string reg_name, int offset);
std::string load_mapped_variable_coprocessor(const Scope *scope, const Node *_var, std::string reg_name);
std::string load_raw_variable(const Scope* scope, std::string addr_reg, std::string reg_name, std::string type_name);
std::string store_mapped_variable(const Scope* scope, const Node* var, std::string reg_name);
std::string store_raw_variable(const Scope* scope, std::string addr_reg, std::string reg_name, std::string type_name);
std::string store_mapped_variable_coprocessor(const Scope *scope, const Node *_var, std::string reg_name);
std::string get_next_register(std::string reg);
std::string allocate_stack_frame(Scope* scope);
std::string deallocate_stack_frame(Scope* scope);
void add_to_global_typemap(Variable_type *var, Scope* scope);

Variable* resolve_variable_name(std::string name, Scope* current);
void try_replace_variable(Node* &varptr, Node* scope);
int resolve_variable_size(std::string name, Scope* child_scope);
int resolve_variable_offset(std::string name, const Scope* current);
std::string intToHex(int value);
std::string convertFloatToBinary(float f);
Variable* allocate_temp_var(Node* current, std::string type);
Variable* resolve_ra_variable(const Node* parent_scope);

Node* resolve_function_call(std::string name, Scope* current);
std::string resolve_base_type(std::string alias, Scope* scope);
std::string resolve_base_codepath(std::string alias, Scope *scope);
int get_log_ptr_element(std::string ptr_type, Scope* scope);
std::string copy_str_literal(std::string ptr_reg, std::string string);

#endif