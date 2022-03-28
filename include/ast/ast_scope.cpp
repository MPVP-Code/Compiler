#include "ast_scope.hpp"
#include "ast_func.hpp"
#include "ast_flow_control.hpp"
#include "ast_stack.hpp"
#include <string>
#include <cctype>

Scope::Scope() {
    this->type = "Scope";
}

void Scope::generate_var_maps(Node *parent) {
    Scope *parentScope = (Scope *) parent;

    this->parent_scope = parentScope;

    //Applies varmaps to conditions
    if (this->subtype == "While") {
        While *flow = (While *) this;
        try_replace_variable(flow->condition, this);

    }
    if (this->subtype == "DoWhile") {
        auto flow = (DoWhile *) this;
        try_replace_variable(flow->condition, this);
    } else if (this->subtype == "If") {
        If *flow = (If *) this;
        try_replace_variable(flow->condition, this);
    } else if (this->subtype == "For") {
        For *flow = (For *) this;
        try_replace_variable(flow->initialization, this);
        try_replace_variable(flow->condition, this);
        try_replace_variable(flow->update, this);
    } else if (this->subtype == "FunctionDeclaration") {
        //Applies varmapping to declared variables
        auto func = (FunctionDeclaration *) this;
        for (Variable* arg: *(func->arguments)) {
            try_replace_variable(reinterpret_cast<Node *&>(arg), this);
        }
    }


    for (auto &node: this->statements) {
        try_replace_variable(node, this);
    }

    if (this->subtype == "If") {
        If *ifScope = (If *) this;

        if (ifScope->truestatements != nullptr) {
            for (auto &node: *ifScope->truestatements) {
                try_replace_variable(node, this);
            }
        }

        if (ifScope->falsestatements != nullptr) {
            for (auto &node: *ifScope->falsestatements) {
                try_replace_variable(node, this);
            }
        }
    }

    //Generates variable offsets
    int offset = 0;
    auto scp = (Scope *) this;
    for (auto &var: scp->var_map) {
        var.second->offset = offset;
        offset += resolve_variable_size(var.second->name, scp);
    }


    //Allocates two extra words for future system use $ra backup, $fp backup
    int extra_words = 2;
    offset += 4 * extra_words;
    if (offset % 4 == 0) {
        this->stack_frame_size = offset;
    } else {
        this->stack_frame_size = offset + (4 - offset % 4);
    }
};


std::vector<Node *> *Scope::getBranches() {
    return &(this->statements);
};

std::string Scope::compileToMIPS(const Node *parent_scope) const {
    throw std::runtime_error(this->type + " compileToMIPS not implemented.");
}


Global::Global() {
    this->type = "Global";
    this->parent_scope = NULL;

    this->type_map["int"] = new Variable_type("int", "none", 4);
    this->type_map["double"] = new Variable_type("double", "none", 8);
    this->type_map["float"] = new Variable_type("float", "none", 4);
    this->type_map["char"] = new Variable_type("char", "none", 1);
    this->type_map["unsigned"] = new Variable_type("unsigned", "none", 4);
}

std::string Global::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    for (Node *statement: this->statements) {
        //Todo Implement switch for global variables
        result += statement->compileToMIPS(this) + "\n";
    }

    return result;
}

int Global::whileCount = 0;
int Global::forCount = 0;
int Global::ifCount = 0;
int Global::logicAndCount = 0;
int Global::logicOrCount = 0;

int Global::getIdForWhile() {
    return whileCount++;
}

int Global::getIdForForLoop() {
    return forCount++;
}

int Global::getIdForIf() {
    return ifCount++;
}

int Global::getIdForLogicAnd() {
    return logicAndCount++;
}

int Global::getIdForLogicOr() {
    return logicOrCount++;
}