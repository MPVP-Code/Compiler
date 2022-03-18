//
// Created by michal on 15. 3. 2022.
//
#include "ast_flow_control.hpp"
#include "ast_assignment.hpp"

While::While(Node* _condition, std::vector<Node*>* _statements): condition(_condition) {
        this->type = "While";
        this->statements = _statements;
}

If::If(Node* _condition, std::vector<Node*>* _truestatements, std::vector<Node*>* _falsestatements): condition(_condition) {
        this->type = "If";
        this->truestatements = _truestatements;
        this->falsestatements = _falsestatements;
}

std::string If::compileToMIPS() const {
    std::string result = "";

    if (condition->get_type().compare("Constant") == 0) {
        Constant *constantCondition = (Constant*) condition;
        if (constantCondition->getValue() == 0 && falsestatements == nullptr) {
            return "";
        } else if (constantCondition->getValue() != 0 && truestatements != nullptr) {
            for (Node *statement : *truestatements) {
                std::string generatedCode = statement->compileToMIPS();
                if (generatedCode.length() != 0) {
                    result += generatedCode + (generatedCode.substr(generatedCode.length() - 1, 1) != "\n" ? "\n" : "");
                }
            }

            result = result.substr(0, result.length() - 1);
        }
    }

    return result;
};