#include <iostream>
#include "ast_stack.hpp"
#include "ast_syntax.hpp"
#include "ast_assignment.hpp"
#include "ast_assignment.hpp"

Variable *resolve_variable_name(std::string name, Scope *current) {
    while (current != NULL) {
        if (current->var_map.contains(name)) {
            return current->var_map.at(name);
        } else {
            current = current->parent_scope;
        }
    }
    return NULL;
};


//Tries to replace variable pointer with mapped variables

void try_replace_variable(Node *&varptr, Node *inscope) {
    Scope *scope = (Scope *) inscope;
    if (varptr->type == "Variable") {
        auto temp = (Variable *) varptr;
        if (temp->declaration) {
            scope->var_map[temp->name] = temp;
        } else {
            varptr = resolve_variable_name(temp->name, scope);
        }
    } else if (varptr->type == "UnaryOperator" && varptr->subtype == "SizeOf") {
        auto temp = (SizeOf *) varptr;
        try_replace_variable(temp->in, inscope);
        int varsize = resolve_variable_size(temp->in->data_type, scope);
        varptr = new Constant(varsize);
    } else {
        varptr->generate_var_maps(scope);
    }
}

int resolve_variable_size(std::string name, Scope *child_scope) {
    Scope *current = child_scope;


    //Try interpreting name as variable name
    std::string type_name = "none";

    while (current != NULL) {
        if (current->var_map.contains(name)) {
            type_name = current->var_map.at(name)->data_type;
            break;
        } else {
            current = current->parent_scope;
        }
    }

    //If success, resolve length
    //If failure, interpret name as type name

    current = child_scope;
    if (type_name == "none") type_name = name;

    while (current != NULL) {
        if (current->type_map.contains(type_name)) {
            return (current->type_map.at(type_name))->size;
        } else {
            current = current->parent_scope;
        }
    }
    return -1000;
};

int resolve_variable_offset(std::string name, const Scope *current) {
    int total_offset = 0;
    while (current != NULL) {
        if (current->var_map.contains(name)) {
            return total_offset + current->var_map.at(name)->offset;
        } else {
            total_offset += current->stack_frame_size;
            current = current->parent_scope;
        }
    }
    std::cerr << "Failed to resolve offset\n";
    return -1;
};

std::string load_mapped_variable(const Scope* scope, const Node* _var, std::string reg_name) {
    auto var = (Variable*) _var;
    int offset = resolve_variable_offset(var->name, scope);
    std::string out = "";
    if (offset % 4 == 0) {
        out = "lw " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
    } else { //Load from unaligned memory addresses
        out += "lwl " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
        out += "lwr " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
    }
    out += "nop\n";
    return out;
}

std::string store_mapped_variable(const Scope *scope, const Node *_var, std::string reg_name) {
    auto var = (Variable*) _var;
    int offset = resolve_variable_offset(var->name, scope);
    std::string out = "";
    if (offset % 4 == 0) {
        out += "sw " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
    } else { //Storing in unaligned memory addresses
        out += "lwl " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
        out += "lwr " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
    }
    out += "nop\n";
    return out;

}

std::string allocate_stack_frame(Scope *scope) {
    std::string out = "";
    int frame_size = -1 * (scope->stack_frame_size +
                           (scope->stack_frame_size % 4 != 0)); //Stack counts down in mips, rounds to full word
    out += "addiu $sp, $sp, " + std::to_string(frame_size) + "\n";
    out += "addiu $fp, $fp, " + std::to_string(frame_size) + "\n";

    return out;
}

std::string deallocate_stack_frame(Scope *scope) {
    std::string out = "";
    int frame_size = (scope->stack_frame_size +
                      (scope->stack_frame_size % 4 != 0)); //Stack counts down in mips, deallocation increases pointer
    out += "addiu $sp, $sp, " + std::to_string(frame_size) + "\n";
    out += "addiu $fp, $fp, " + std::to_string(frame_size) + "\n";
    return out;
}

std::string intToHex(int value) {
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(value)) << std::hex << value;
    return stream.str();
}

Variable* allocate_temp_var(Node* _current, std::string type){
    auto current = (Scope*) _current;

    std::string tmpname = "!tmp" + std::to_string(current->tmp_var_counter++);
    auto var = new Variable(type, tmpname , true);

    current->var_map[tmpname] = var;

    return var;
}
