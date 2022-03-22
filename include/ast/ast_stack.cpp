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


//Tries to replace variable pointer with mapped variables

void try_replace_variable(Node* &varptr, Node* inscope){
    Scope* scope = (Scope*) inscope;
    if (varptr->type == "Variable" ){
        auto temp = (Variable*) varptr;
        if(temp->declaration) {
            scope->var_map[temp->name] = temp;
        }
        else {
            varptr = resolve_variable_scope(temp->name, scope);
        }
    }
    else{
        varptr->generate_var_maps(scope);
    }
}