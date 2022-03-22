//
// Created by michal on 22. 3. 2022.
//

#ifndef AST_STACK_HPP
#define AST_STACK_HPP

#include "ast_scope.hpp"


void load_mapped_variable(Scope* scope, Variable* var, std::string reg_name); //reg_name inserted directly into lw instruction.
void store_mapped_variable(Scope* scope, Variable* var, std::string reg_name);
void allocate_stack_frame(Scope* scope);
void deallocate_stack_frame(Scope* scope);

Variable* resolve_variable_name(std::string name, Scope* current);
void try_replace_variable(Node* &varptr, Node* scope);
int resolve_variable_size(std::string name, Scope* child_scope);
int resolve_variable_offset(std::string name, Scope* current);


//void save_function_context();
//void restore_function_context();

#endif
