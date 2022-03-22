//
// Created by michal on 22. 3. 2022.
//

#ifndef AST_STACK_HPP
#define AST_STACK_HPP

#include "ast_scope.hpp"

Variable* resolve_variable_scope(std::string name, Scope* current);
void load_mapped_variable(Scope* scope, Variable* var, std::string reg_name); //reg_name inserted directly into lw instruction.
void store_mapped_variable(Scope* scope, Variable* var, std::string reg_name);

//void save_function_context();
//void restore_function_context();

#endif
