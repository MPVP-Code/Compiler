#include "ast_func.hpp"
#include "ast_node.hpp"
#include "ast_stack.hpp"

#include <vector>

FunctionDeclaration::FunctionDeclaration() {  //std::string _return_type, std::string _name, std::vector<Node*> _statements
    //Type specification
    this->type = "Scope";
    this->subtype = "FunctionDeclaration";
    this->forward_declaration = false;

    //Allocate one variable for return address
    this->var_map["!ra"] = new Variable("int", "!ra", true);
}

std::string FunctionDeclaration::compileToMIPS(const Node *parent_scope) const {
    std::cerr << "Compiling function " << this->name << std::endl;
    std::string result = "";

    //Set array init flag to false;
    ((FunctionDeclaration*) this)->array_init_flag = false;

    //Do not compile forward declarations
    if (!forward_declaration) {

        //Function signature generation
        result += ".globl " + generate_function_signature() + "\n";
        result += generate_function_signature() + ":\n";
        result += ".set noreorder\n\n";

        //Allocate scope
        result += allocate_stack_frame((Scope *) this);

        //Saving passed parameters
        int intIdx = 4;
        int floatIdx = 12;
        for (auto param: *arguments) {
            std::string baseType = resolve_base_type(param->data_type, (Scope*) parent_scope);
            if ((baseType == "float" || baseType == "double") && floatIdx <= 14) {
                result += store_mapped_variable_coprocessor((Scope *) this, param, "$f" + std::to_string(floatIdx));
                if (baseType == "float") {
                    intIdx++;
                } else {
                    intIdx += 2;
                }
                if (floatIdx == 14) {
                    intIdx = 6;
                }
                floatIdx += 2;
            } else {

                result += store_mapped_variable((Scope *) this, param, "$" + std::to_string(intIdx));

                //Two word store - skip register
                if (resolve_variable_size(param->name, (Scope *) this) > 4) {
                    intIdx += 2;
                } else {
                    intIdx++;
                }
            }
        }

        //Compile body
        for (Node *statement: statements) {
            std::cerr << "Compiling statement " << statement->get_type() << std::endl;

            //Tells array pointer to initialize
            if (statement->type == "Variable" && ((Variable*) statement)->array_size > 0) ((FunctionDeclaration*) this)->array_init_flag = true;

            std::string compiledCode = statement->compileToMIPS(this);

            //Prevents other calls to variable to compile themselves
            ((FunctionDeclaration*) this)->array_init_flag = false;

            if (compiledCode.length() > 0) {
                result += compiledCode + "\n";
            }
        }

        //Appends implicit returns for void and int types
        //Deallocate scope if not already returned
        result += deallocate_stack_frame((Scope *) this);

        if (return_type == "void") {
            result += "\njr $31\nnop\n\n";
        } else if (return_type == "int") {
            //implicit error code 0
            result += "\nli $v0, 0\n";
            result += "\njr $31\nnop\n\n";
        }

    }
    return result;
};

std::string *FunctionDeclaration::getName() {
    return &(this->name);
}

FunctionDeclaration::~FunctionDeclaration() {}

std::string FunctionDeclaration::generate_function_signature() const {
//    std::string result = name + "(";
//    for (auto arg : *arguments){
//        result += arg->data_type + ", ";
//    }
//    if (arguments->size()>0) {
//        result = result.substr(0, result.length() - 1) ;
//    }
//    return result+ ")";

    return name;
}

FunctionCall::FunctionCall(std::string _function_name, std::vector<Node *> *_arguments) : function_name(
        _function_name) {
    this->type = "FunctionCall";
    this->arguments = _arguments;
};

void FunctionCall::generate_var_maps(Node *parent) {

    //Applies varmapping to parameters
    auto scope = (Scope *) parent;
    this->declaration = (FunctionDeclaration *) resolve_function_call(function_name, ((Scope *) parent));
    this->data_type = declaration->return_type;
    this->result_var = allocate_temp_var(parent, this->data_type);

    for (unsigned int i = 0; i < this->arguments->size(); i++) {
        try_replace_variable((*arguments)[i], scope);
    }
}


std::string FunctionCall::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    //Load parameters into registers
    int idx = 4; // First arg register

    //Save return address
    Variable *ra = resolve_ra_variable(parent_scope);
    result += store_mapped_variable((Scope *) parent_scope, ra, "$ra");

    // Allocate more stack space to prevent memory violation accesses
    int offset = (arguments->size() + 4) * 4;
    result += "addiu $sp, $sp, " + std::to_string(-1 * offset) + "\n";

    for (unsigned int i = 0; i < (*arguments).size(); i++) {
        Node* param = (*arguments)[i];
        result += "addiu $sp, $sp, " + std::to_string(offset) + "\n";
        result += param->compileToMIPS(parent_scope);
        result += "addiu $sp, $sp, " + std::to_string(-1 * offset) + "\n";

        std::string regname = "$" + std::to_string(idx);
        result += load_mapped_variable_with_offset((Scope *) parent_scope, param->get_intermediate_variable(), regname, offset);

        if (i >= 4) {
            result += "sw " + regname + ", " + std::to_string(offset - 4 * (arguments->size() + 4 - i)) + "($sp)\n";
        }

        //Two word load - skip register
        if (resolve_variable_size(((Variable *) param->get_intermediate_variable())->name, (Scope *) parent_scope) >
            4) {
            idx += 2;
        } else {
            idx++;
        }
    }

    //Jump
    result += "jal " + declaration->generate_function_signature() + "\n";
    result += "nop\n";

    result += "addiu $sp, $sp, " + std::to_string(offset) + "\n";

    //const Node* constIntermediate = get_intermediate_variable();
    result += store_mapped_variable((Scope*) parent_scope, result_var, "$v0");

    //Restore return address
    result += load_mapped_variable((Scope *) parent_scope, ra, "$ra");
    return result;
}

Node *FunctionCall::get_intermediate_variable() {
    return result_var;
}


