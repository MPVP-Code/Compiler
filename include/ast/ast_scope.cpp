#include "ast_scope.hpp"
#include "ast_func.hpp"
#include "ast_flow_control.hpp"
#include "ast_stack.hpp"
#include <string>

Scope::Scope() {
    this->type = "Scope";
}

void Scope::generate_var_maps(Node* parent) {
    Scope *parentScope = (Scope*) parent;
    for (auto &node: this->statements) {

        if (node->type == "Scope") {
            Scope *scope = (Scope *) node;
            scope->parent_scope = this;

            //Applies varmaps to conditions
            if (scope->subtype == "While") {
                While* flow = (While *) scope;
                try_replace_variable(flow->condition, scope);

            } else if (scope->subtype == "If") {
                If* flow = (If *) scope;
                try_replace_variable(flow->condition, scope);
            }
            scope->generate_var_maps(scope);

        }else {
            try_replace_variable(node, this);
        }

    }
    //Generate scope offsets & allocate stack memory.
    int offset = 0;



    for(auto &var : this->var_map){
        var.second->offset = offset;
        offset += resolve_variable_size(var.second->data_type, this);
    }

    //Allocates two extra words for future system use $ra backup, $spfp backup
    int extra_words = 2;
    offset += 4*extra_words;
    this->stack_frame_size = offset;

};


std::vector<Node*>* Scope::getBranches() {
    return &(this->statements);
};

std::string Scope::compileToMIPS() const {
    throw std::runtime_error(this->type + " compileToMIPS not implemented.");
}


Global::Global() {
    this->type = "Global";
    this->parent_scope = NULL;

    this->type_map["int"] = new Variable_type("int", "none", 4);
    this->type_map["int"] = new Variable_type("double", "none", 4);
    this->type_map["int"] = new Variable_type("float", "none", 2);
    this->type_map["int"] = new Variable_type("char", "none", 1);
    this->type_map["int"] = new Variable_type("unsigned", "int", 4);
}

std::string Global::compileToMIPS() const {
    std::string result = "";

    for (Node *statement: this->statements) {
        std::cerr << "statement->get_type(): " << statement->get_type()  << "subtype: " << statement->getSubtype() << std::endl;
        if (statement->get_type().compare("FunctionDeclaration") == 0 || statement->getSubtype().compare("FunctionDeclaration") == 0) {
            FunctionDeclaration *function = (FunctionDeclaration*) statement;
            result += ".globl " + *(function->getName()) + "\n";
        }
    }

    for (Node *statement : this->statements) {
        result += statement->compileToMIPS() + "\n";
    }

    return result;
}

int Global::whileCount = 0;

int Global::getIdForWhile() {
    return whileCount++;
}