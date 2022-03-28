#include "ast_flow_control.hpp"
#include "ast_stack.hpp"

While::While(Node *_condition, std::vector<Node *> _statements) : Scope(), condition(_condition) {
    this->subtype = "While";
    this->statements = _statements;
}

std::string While::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    result += allocate_stack_frame((Scope *) this);
    result += condition->compileToMIPS((Scope *) this) + "\n";
    int whileId = Global::getIdForWhile();
    std::string whileStart = "$WHILE" + std::to_string(whileId) + "START";
    std::string whileEnd = "$WHILE" + std::to_string(whileId) + "END";
    result += whileStart + ":\n";
    result += load_mapped_variable((Scope *) this, condition->get_intermediate_variable(), "$15");
    result += "beq $15, $0, " + whileEnd + "\nnop\n";

    for (Node *statement: statements) {
        std::string generatedCode = statement->compileToMIPS(this);
        if (generatedCode.length() != 0) {
            result += generatedCode + (generatedCode.substr(generatedCode.length() - 1, 1) != "\n" ? "\n" : "");
        }
    }
    result += condition->compileToMIPS((Scope *) this) + "\n";
    result += "b " + whileStart + "\nnop\n";
    result += whileEnd + ":" + "\n";

    result += deallocate_stack_frame((Scope *) this);

    return result.substr(0, result.length() - 1);
}

DoWhile::DoWhile(Node *_condition, std::vector<Node *> _statements) : Scope(), condition(_condition) {
    this->subtype = "DoWhile";
    this->statements = _statements;
}

std::string DoWhile::compileToMIPS(const Node *parent_scope) const {}


If::If(Node *_condition, std::vector<Node *> *_truestatements, std::vector<Node *> *_falsestatements)
        : Scope(), condition(_condition) {
    this->subtype = "If";
    this->truestatements = _truestatements;
    this->falsestatements = _falsestatements;
}

std::string If::compileStatementsToMIPS(std::vector<Node *> *statements) const {
    std::string result = "";

    for (Node *statement: *statements) {
        std::string generatedCode = statement->compileToMIPS(this);
        if (generatedCode.length() != 0) {
            result += generatedCode + (generatedCode.substr(generatedCode.length() - 1, 1) != "\n" ? "\n" : "");
        }
    }

    return result.substr(0, result.length() - 1);
}

std::string If::compileToMIPS(const Node *parent_scope) const {
    std::string result = condition->compileToMIPS(parent_scope);
    int ifId = Global::getIdForIf();
    result += load_mapped_variable((Scope *) parent_scope, condition->get_intermediate_variable(), "$15");
    result += allocate_stack_frame((Scope *) this);
    std::string elseLabel = "$ELSE" + std::to_string(ifId);
    std::string ifEndLabel = "$IFEND" + std::to_string(ifId);
    result += "beq $15, $0, " + elseLabel + "\nnop\n";

    if (truestatements != nullptr) {
        result += this->compileStatementsToMIPS(this->truestatements) + "\n";
        result += "b " + ifEndLabel + "\nnop\n";
    }

    result += elseLabel + ":\n";

    if (falsestatements != nullptr) {
        result += this->compileStatementsToMIPS(this->falsestatements) + "\n";
    }
    result += ifEndLabel + ":\n";
    result += deallocate_stack_frame((Scope *) this);

    return result;
}

For::For(Node *_initialization, Node *_condition, Node *_update, std::vector<Node *> _statements)
        : Scope(), initialization(_initialization), condition(_condition), update(_update) {
    this->subtype = "For";
    this->statements = _statements;
}

std::string For::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    int forId = Global::getIdForForLoop();
    std::string forCondLabel = "$FORCOND" + std::to_string(forId);
    std::string forStatementLabel = "$FORSTATEMENTS" + std::to_string(forId);

    result += allocate_stack_frame((Scope *) this);
    result += initialization->compileToMIPS((Scope *) this) + "\n";
    result += "b " + forCondLabel + "\n";
    result += forStatementLabel + ":\n";

    for (Node *statement: statements) {
        std::string generatedCode = statement->compileToMIPS(this);
        if (generatedCode.length() != 0) {
            result += generatedCode + (generatedCode.substr(generatedCode.length() - 1, 1) != "\n" ? "\n" : "");
        }
    }
    result += update->compileToMIPS((Scope *) this) + "\n";
    result += forCondLabel + ":\n";
    result += condition->compileToMIPS((Scope *) this) + "\n";
    result += load_mapped_variable((Scope *) this, condition->get_intermediate_variable(), "$15") + "\n";
    result += "bne $15, $0, " + forStatementLabel + "\n";
    result += "nop\n";
    result += deallocate_stack_frame((Scope *) this);
    return result;
}

Switch::Switch(Node *_condition, std::vector<Node *> _statements) : condition(_condition), statements(_statements) {
    this->type = "Switch";
}

std::string Switch::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    int switchId = Global::getIdForSwitch();
    int caseCounter = 0;
    std::string switchEndLabel = "$SWITCH_END_" + std::to_string(switchId);
    std::string caseEndLabel = "";
    result += condition->compileToMIPS(parent_scope);
    for (unsigned int i = 0; i < statements.size(); i++) {
        if (statements[i]->type == "Break") {
            result += "b " + switchEndLabel + "\nnop\n";
            if (caseEndLabel.length() > 0) {
                result += caseEndLabel + ":\n";
                caseEndLabel = "";
            }
        } else if (statements[i]->type == "Case") {
            if (caseEndLabel.length() > 0) {
                result += caseEndLabel + ":\n";
            }
            caseEndLabel = "$CASE_" + std::to_string(switchId) + "_END_" + std::to_string(caseCounter);
            Case* caseStatement = (Case*) statements[i];
            result += caseStatement->compileCaseToMIPS(parent_scope, (Variable *) condition->get_intermediate_variable(), caseEndLabel);
            caseCounter++;
        } else if (statements[i]->type == "DefaultCase") {
            if (caseEndLabel.length() > 0) {
                result += caseEndLabel + ":\n";
                caseEndLabel = "";
            }
            result += statements[i]->compileToMIPS(parent_scope) + "\n";
        } else {
            result += statements[i]->compileToMIPS(parent_scope) + "\n";
        }
    }
    if (caseEndLabel.length() > 0) {
        result += caseEndLabel + ":\n";
    }
    result += switchEndLabel + ":\n";
    return result;
}

void Switch::generate_var_maps(Node *parent) {
    try_replace_variable(condition, parent);
    for (Node* statement: statements) {
        try_replace_variable(statement, parent);
    }
}

Case::Case(Node *_constant, std::vector<Node*> _statements): constant(_constant), statements(_statements) {
    this->type = "Case";
}

void Case::generate_var_maps(Node *parent) {
    try_replace_variable(constant, parent);
    for (Node* statement: statements) {
        try_replace_variable(statement, parent);
    }
}

std::string Case::compileToMIPS(const Node *parent_scope) const {
    return "";
}

std::string Case::compileCaseToMIPS(const Node *parent_scope, Variable* condition, std::string caseEndLabel) const {
    std::string result = constant->compileToMIPS(parent_scope) + "\n";
    result += load_mapped_variable((Scope *) parent_scope, constant->get_intermediate_variable(), "$15") + "\n";
    result += load_mapped_variable((Scope *) parent_scope, condition->get_intermediate_variable(), "$14") + "\n";
    result += "bne $15, $14, " + caseEndLabel + "\nnop\n";

    for (Node* statement: statements) {
        result += statement->compileToMIPS(parent_scope);
    }

    return result;
}

DefaultCase::DefaultCase(std::vector<Node*> _statements): statements(_statements) {
    this->type = "DefaultCase";
}

std::string DefaultCase::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    for (Node* statement: statements) {
        result += statement->compileToMIPS(parent_scope);
    }
    return result;
}

void DefaultCase::generate_var_maps(Node *parent) {
    for (Node* statement: statements) {
        try_replace_variable(statement, parent);
    }
}

Break::Break() {
    this->type = "Break";
}

std::string Break::compileToMIPS(const Node *parent_scope) const {
    return "";
}

void Break::generate_var_maps(Node *parent) {
    return;
}
