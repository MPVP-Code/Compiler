//
// Created by michal on 15. 3. 2022.
//
#include "ast_flow_control.hpp"

While::While(Node* _condition, std::vector<Node*>* _statements): condition(_condition) {
        this->type = "While";
        this->statements = _statements;
}


If::If(Node* _condition, std::vector<Node*>* _truestatements, std::vector<Node*>* _falsestatements): condition(_condition) {
        this->type = "If";
        this->truestatements = _truestatements;
        this->falsestatements = _falsestatements;
}