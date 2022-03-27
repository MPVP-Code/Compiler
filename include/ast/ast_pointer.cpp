//
// Created by michal on 27. 3. 2022.
//
#include "ast_pointer.hpp"

AddressOf::AddressOf(Node *in) : UnaryOperator(in) {

}

std::string AddressOf::compileToMIPS(const Node *parent_scope) const {
    return Node::compileToMIPS(parent_scope);
}

Dereference::Dereference(Node *in) : UnaryOperator(in) {

}

std::string Dereference::compileToMIPS(const Node *parent_scope) const {
    return Node::compileToMIPS(parent_scope);
}


