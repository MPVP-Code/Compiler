//
// Created by Michal on 22. 3. 2022.
//
#include "ast_stack.hpp"

void load_mapped_variable(Scope* scope, Variable* var, std::string reg_name) {}
void store_mapped_variable(Scope* scope, Variable* var, std::string reg_name){}

Variable* resolve_variable_scope(std::string name, Scope* current){
    while(current != NULL){
        if(current->var_map.contains(name)){
            return current->var_map.at(name);
        }
        else{
            current = current->parent_scope;
        }
    }
    return NULL;
};