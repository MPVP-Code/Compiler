//
// Created by Michal on 22. 3. 2022.
//
#include "ast_stack.hpp"

Variable* resolve_variable_name(std::string name, Scope* current){
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
            varptr = resolve_variable_name(temp->name, scope);
        }
    }
    else{
        varptr->generate_var_maps(scope);
    }
}

int resolve_variable_size(std::string name, Scope* child_scope){
    Scope* current = child_scope;


    //Try interpreting name as variable name
    std::string type_name = "none";

    while(current != NULL){
        if(current->var_map.contains(name)){
            type_name = current->var_map.at(name)->type;
            break;
        }
        else{
            current = current->parent_scope;
        }
    }

    //If success, resolve length
    //If failure, interpret name as type name

    current = child_scope;
    if(type_name == "none") type_name = name;

    while(current != NULL){
        if(current->type_map.contains(name)){
            return (current->type_map.at(name))->size;
        }
        else{
            current = current->parent_scope;
        }
    }
    return -1000;
};

int resolve_variable_offset(std::string name, Scope* current){
    int total_offset = 0;
    while(current != NULL){
        if(current->var_map.contains(name)){
            return total_offset + current->var_map.at(name)->offset;
        }
        else{
            total_offset += current->stack_frame_size;
            current = current->parent_scope;
        }
    }
    std::cerr<<"Failed to resolve offset\n";
    return -1;
};

void load_mapped_variable(Scope* scope, Variable* var, std::string reg_name) {
    int offset = resolve_variable_offset(var->name, scope );
    std::cout<< "lw "<<reg_name<<", "<<offset<<"($sp)" << std::endl;
}
void store_mapped_variable(Scope* scope, Variable* var, std::string reg_name){
    int offset = resolve_variable_offset(var->name, scope );
    std::cout<< "sw "<<reg_name<<", "<<offset<<"($sp)" << std::endl ;
}

void allocate_stack_frame(Scope* scope){
    int frame_size =  -1 * scope->stack_frame_size; //Stack counts down in mips
    std::cout << "addiu $sp, $sp, "<<frame_size << std::endl;
    std::cout << "addiu $fp, $fp, "<<frame_size << std::endl;

}
void deallocate_stack_frame(Scope* scope){
    int frame_size = scope->stack_frame_size; //Stack counts down in mips, deallocation increases pointer
    std::cout << "addiu $sp, $sp, "<<frame_size << std::endl;
    std::cout << "addiu $fp, $fp, "<<frame_size << std::endl;

}
