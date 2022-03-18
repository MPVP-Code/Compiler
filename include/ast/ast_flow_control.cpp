//
// Created by michal on 15. 3. 2022.
//
#include "ast_flow_control.hpp"

While::While(Node* _condition, std::vector<Node*>* _statements): Scope(), condition(_condition){
        this->subtype = "While";
        this->statements = _statements;
}


If::If(Node* _condition, std::vector<Node*>* _truestatements, std::vector<Node*>* _falsestatements): Scope(), condition(_condition) {
        this->subtype = "If";
        this->truestatements = _truestatements;
        this->falsestatements = _falsestatements;
}