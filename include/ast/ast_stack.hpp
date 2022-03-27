//
// Created by michal on 22. 3. 2022.
//

#ifndef AST_STACK_HPP
#define AST_STACK_HPP

#include "ast_scope.hpp"
#include "ast_func.hpp"


std::string load_mapped_variable(const Scope* scope, const Node* var, std::string reg_name);
std::string load_mapped_variable_rec(const Scope* scope, const Node* var, std::string reg_name, int size_remaining); //reg_name inserted directly into lw instruction.
std::string store_mapped_variable(const Scope* scope, const Node* var, std::string reg_name);
std::string get_next_register(std::string reg);
std::string allocate_stack_frame(Scope* scope);
std::string deallocate_stack_frame(Scope* scope);

Variable* resolve_variable_name(std::string name, Scope* current);
void try_replace_variable(Node* &varptr, Node* scope);
int resolve_variable_size(std::string name, Scope* child_scope);
int resolve_variable_offset(std::string name, Scope* current);
std::string intToHex(int value);
Variable* allocate_temp_var(Node* current, std::string type);

Node* resolve_function_call(std::string name, Scope* current);

//void save_function_context();
//void restore_function_context();

#endif