#include <iostream>
#include <iomanip>
#include <string>
#include "ast_stack.hpp"
#include "ast_syntax.hpp"
#include "ast_assignment.hpp"
#include "ast_arithmetic.hpp"

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

            //If pointer try adding to type map
            if (varptr->data_type.at(varptr->data_type.length() - 1) == '*') {
                auto type = new Variable_type(varptr->data_type, "int", 4);
                add_to_global_typemap(type, scope);
            }
            //Else just resolve type
            scope->var_map[temp->name] = temp;
        } else {
            varptr = resolve_variable_name(temp->name, scope);
        }
    } else if (varptr->type == "UnaryOperator" && varptr->subtype == "SizeOf") {
        auto temp = (SizeOf *) varptr;
        try_replace_variable(temp->in, inscope);
        int varsize = resolve_variable_size(temp->in->data_type, scope);
        varptr = new Constant(varsize);
        varptr->generate_var_maps(scope);
    } else if (varptr->type == "UnaryOperator" && (varptr->subtype == "PostIncOp" || varptr->subtype == "PostDecOp")) {
        auto temp = (PostIncOp *) varptr;
    } else if (varptr->type == "Identifier") {
        auto identifier = (Identifier *) varptr;
        varptr = resolve_variable_name(identifier->identifier, scope);
    } else {
        varptr->generate_var_maps(scope);
    }
}

int resolve_variable_size(std::string name, Scope *child_scope) {
    Scope *current = (Scope *) child_scope;


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

    current = (Scope *) child_scope;
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

std::string get_next_register(std::string reg) {
    if (std::isdigit(reg.at(1))) {
        //Name is of type $number
        return "$" + std::to_string(std::stoi(reg.substr(1, reg.size() - 1)) + 1);
    } else if (std::isdigit(reg.at(2))) {

        //Easiest solution :(
        if (reg == "$v0") return "$v1";
        else if (reg == "$v1") return "$a0";
        else if (reg == "$a0") return "$a1";
        else if (reg == "$a1") return "$a2";
        else if (reg == "$a2") return "$a3";
        else if (reg == "$a3") return "$t0";
        else if (reg == "$t0") return "$t1";
        else if (reg == "$t1") return "$t2";
        else if (reg == "$t2") return "$t3";
        else if (reg == "$t3") return "$t4";
        else if (reg == "$t4") return "$t5";
        else if (reg == "$t5") return "$t6";
        else if (reg == "$t6") return "$t7";
        else if (reg == "$t7") return "$t8";
        else if (reg == "$t8") return "$t9";
        else {
            std::cerr << "failed to determine next register\n";
            return "";
        }
    } else {
        std::cerr << "failed to determine next register\n";
        return "";
    }

}

std::string load_mapped_variable_with_offset(const Scope *scope, const Node *_var, std::string reg_name, int additionalOffset) {
    auto var = (Variable *) _var;
    std::string out = "";
    int var_size = resolve_variable_size(var->data_type, (Scope *) scope);

//Check if variable refers to function return
    if (var->name == "!return") {
        //If sub 1 word type
        if (var_size <= 4) {
            out += "move " + reg_name + ", $v0\n";
        } else {
            //If 2 word type
            out += "move " + reg_name + ", $v0\n";
            out += "move " + get_next_register(reg_name) + ", $v1\n";
        }

    } else {
        int offset = resolve_variable_offset(var->name, scope) + additionalOffset;

        //Load 4 byte word
        if (var_size == 4) {
            //Load first word
            if (offset % 4 == 0) {
                out = "lw " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
            } else { //Load from unaligned memory addresses
                out += "lwr " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
                out += "lwl " + reg_name + ", " + std::to_string(offset + 3) + "($sp)\n";
            }
            out += "nop\n";
        }
            //Load 8 byte word
        else if (var_size == 8) {

            //Load left word
            if (offset % 4 == 0) {
                out = "lw " + reg_name + ", " + std::to_string(offset + 4) + "($sp)\n";
            } else { //Load from unaligned memory addresses
                out += "lwr " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
                out += "lwl " + reg_name + ", " + std::to_string(offset + 3) + "($sp)\n";
            }
            out += "nop\n";

            //Load right word
            if (offset % 4 == 0) {
                out = "lw " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
            } else { //Load from unaligned memory addresses
                out += "lwr " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
                out += "lwl " + reg_name + ", " + std::to_string(offset + 3) + "($sp)\n";
            }
            out += "nop\n";

            //Load byte
        } else if (var_size == 1) {
            out += "lb " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
        }

    }
    return out;
}

std::string load_mapped_variable(const Scope *scope, const Node *var, std::string reg_name) {
    return load_mapped_variable_with_offset(scope, var, reg_name, 0);
}

std::string load_raw_variable(const Scope *scope, std::string addr_reg, std::string reg_name, std::string type_name) {
    std::string out = "#Raw variable load\n";
    int var_size = resolve_variable_size(type_name, (Scope *) scope);

//Check if variable refers to function return

    //Load 4 byte word
    if (var_size == 4) {
        //Load first word
        out += "lwr " + reg_name + ", 0(" + addr_reg + ")\n";
        out += "lwl " + reg_name + ", 3(" + addr_reg + ")\n";
        out += "nop\n";
    }
        //Load 8 byte word
    else if (var_size == 8) {

        //Load left word
        out += "lwr " + reg_name + ", 4(" + addr_reg + ")\n";
        out += "lwl " + reg_name + ", 7(" + addr_reg + ")\n";
        out += "nop\n";

        //Load right word
        out += "lwr " + get_next_register(reg_name) + ", 0(" + addr_reg + ")\n";
        out += "lwl " + get_next_register(reg_name) + ", 3(" + addr_reg + ")\n";
        out += "nop\n";

        //Load byte
    } else if (var_size == 1) {
        out += "lb " + reg_name + ", 0(" + addr_reg + ")\n";
    }


    return out;
}


std::string load_mapped_variable_coprocessor(const Scope *scope, const Node *_var, std::string reg_name) {
    auto var = (Variable *) _var;
    std::string out = "";


    if (var->name != "!return") {
        int offset = resolve_variable_offset(var->name, scope);
        //Only spports aligned offsets
        if (offset % 4 == 0) {
            out = "lwc1 " + reg_name + ", " + std::to_string(offset) + "($sp) \n";
        }
        out += "nop\n";
    } else {
        //Only load one register if small type
        if (resolve_variable_size(var->data_type, (Scope *) scope) <= 4) {
            out += "move " + reg_name + ", $v0";
        }

    }


    return out;
}


std::string store_mapped_variable(const Scope *scope, const Node *_var, std::string reg_name) {
    auto var = (Variable *) _var;
    int offset = resolve_variable_offset(var->name, scope);
    int var_size = resolve_variable_size(var->data_type, (Scope *) scope);

    std::string out = "";

    //Store 4 byte var
    if (var_size == 4) {
        if (offset % 4 == 0) {
            out += "sw " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
        } else { //Storing in unaligned memory addresses
            out += "swr " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
            out += "swl " + reg_name + ", " + std::to_string(offset + 3) + "($sp)\n";
        }
        out += "nop\n";


        //Load 8 byte var
    } else if (var_size == 8) {

        //Load left word
        if (offset % 4 == 0) {
            out = "sw " + reg_name + ", " + std::to_string(offset + 4) + "($sp)\n";
        } else { //Load from unaligned memory addresses
            out += "swr " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
            out += "swl " + reg_name + ", " + std::to_string(offset + 3) + "($sp)\n";
        }
        out += "nop\n";

        //Load right word
        if (offset % 4 == 0) {
            out = "sw" + reg_name + ", " + std::to_string(offset) + "($sp)\n";
        } else { //Load from unaligned memory addresses
            out += "swr " + reg_name + ", " + std::to_string(offset + 4) + "($sp)\n";
            out += "swl " + reg_name + ", " + std::to_string(offset + 3 + 4) + "($sp)\n";
        }
        out += "nop\n";

        //store byte
    } else if (var_size == 1) {
        out += "sb " + reg_name + ", " + std::to_string(offset) + "($sp)\n";
    }

    return out;
}

std::string store_mapped_variable_coprocessor(const Scope *scope, const Node *_var, std::string reg_name) {
    auto var = (Variable *) _var;
    std::string out = "";


    if (var->name != "!return") {
        int offset = resolve_variable_offset(var->name, scope);
        //Only spports aligned offsets
        if (offset % 4 == 0) {
            out = "swc1 " + reg_name + ", " + std::to_string(offset) + "($sp) \n";
        }
        out += "nop\n";
    } else {
        //Only load one register if small type
        if (resolve_variable_size(var->data_type, (Scope *) scope) <= 4) {
            out += "mfc1 " + reg_name + ", $v0";
        }

    }


    return out;
}

std::string allocate_stack_frame(Scope *scope) {
    std::string out = "";

    out += "addiu $sp, $sp, " + std::to_string(-1 * (scope->stack_frame_size)) + "\n";

    //fp operations
    //out += "addiu $fp, $sp\n";
    //out += "addiu $fp, $fp, " + std::to_string(frame_size) + "\n";

    return out;
}

std::string deallocate_stack_frame(Scope *scope) {
    std::string out = "";

    out += "addiu $sp, $sp, " + std::to_string(scope->stack_frame_size) + "\n";

    //fp operations
    //out += "addiu $fp, $fp, " + std::to_string(frame_size) + "\n";
    return out;
}

void add_to_global_typemap(Variable_type *var, Scope *scope) {
    while (scope->parent_scope != NULL) {
        scope = scope->parent_scope;
    }
    if (!scope->type_map.contains(var->name)) {
        scope->type_map[var->name] = var;
    }
}

std::string intToHex(int value) {
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(value)) << std::hex << value;
    return stream.str();
}

Variable *allocate_temp_var(Node *_current, std::string type) {
    auto current = (Scope *) _current;

    std::string tmpname = "!tmp" + std::to_string(current->tmp_var_counter++);
    auto var = new Variable(type, tmpname, true);

    current->var_map[tmpname] = var;

    return var;
}


Node *resolve_function_call(std::string name, Scope *current) {
    while (current->parent_scope != NULL) {
        current = current->parent_scope;
    }

    auto global = (Global *) current;
    return global->declaration_map[name];
}

std::string resolve_base_type(std::string alias, Scope *scope) {
    Scope *current_scope = scope;
    std::string current_alias = alias;
    std::string base;

    while (current_alias != "none") {
        int a = current_scope->type_map.contains(alias);
        while (!(current_scope->type_map.contains(alias))) {
            current_scope = current_scope->parent_scope;
        }
        base = current_alias;
        current_alias = current_scope->type_map[current_alias]->aliasof;

    }
    return base;
}