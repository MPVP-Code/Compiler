//
// Created by michal on 15. 3. 2022.
//
#include "ast_flow_control.hpp"
#include "ast_assignment.hpp"

While::While(Node* _condition, std::vector<Node*> _statements): Scope(), condition(_condition){
        this->subtype = "While";
        this->statements = _statements;
}

std::string While::compileToMIPS() const {
    std::string result = "";
    if (condition->get_type().compare("Constant") == 0) {
        Constant *constant = (Constant*) condition;
        if (constant->getValue() == 0) {
            return "";
        }
    } else if (condition->get_type().compare("Variable") == 0) {
        Variable *conditionVariable = (Variable *) condition;
        int whileId = Global::getIdForWhile();
        std::string whileStart = "$WHILE" + std::to_string(whileId) + "START";
        std::string whileEnd = "$WHILE" + std::to_string(whileId) + "END";
        result += whileStart + ":\n";
        int conditionRegister = RegisterAllocator::getRegisterNumberForVariable(conditionVariable->getName());
        result += "beq $" + std::to_string(conditionRegister) + ", $0, " + whileEnd + "\nnop\n";

        for (Node *statement : statements) {
            std::string generatedCode = statement->compileToMIPS();
            if (generatedCode.length() != 0) {
                result += generatedCode + (generatedCode.substr(generatedCode.length() - 1, 1) != "\n" ? "\n" : "");
            }
        }

        result += "b " + whileStart + "\nnop\n";
        result += whileEnd + ":" + "\n";
    }

    return result.substr(0, result.length() - 1);
}

If::If(Node* _condition, std::vector<Node*>* _truestatements, std::vector<Node*>* _falsestatements): Scope(), condition(_condition) {
        this->subtype = "If";
        this->truestatements = _truestatements;
        this->falsestatements = _falsestatements;
}

std::string If::compileStatementsToMIPS(std::vector<Node*>* statements) const {
    std::string result = "";

    for (Node *statement : *statements) {
        std::string generatedCode = statement->compileToMIPS();
        if (generatedCode.length() != 0) {
            result += generatedCode + (generatedCode.substr(generatedCode.length() - 1, 1) != "\n" ? "\n" : "");
        }
    }

    return result.substr(0, result.length() - 1);
}

std::string If::compileToMIPS() const {
    std::string result = "";

    if (condition->get_type().compare("Constant") == 0) {
        Constant *constantCondition = (Constant*) condition;
        if (constantCondition->getValue() == 0 && falsestatements == nullptr) {
            return "";
        } else if (constantCondition->getValue() == 0 && falsestatements != nullptr) {
            result = compileStatementsToMIPS(falsestatements);
        } else if (constantCondition->getValue() != 0 && truestatements != nullptr) {
            result = compileStatementsToMIPS(truestatements);
        }
    }

    return result;
};