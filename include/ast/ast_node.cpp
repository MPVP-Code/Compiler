#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "ast_node.hpp"
#include "ast_variable.hpp"

Node::Node() {
    this->type = "Node";
}

std::string Node::get_type() {
    return this->type;
}

std::string Node::getSubtype() {
    return this->subtype;
}
double Node::compile() const {
    throw std::runtime_error(this->type + "compile not implemented.");
}

double Node::print() const {
    throw std::runtime_error(this->type + " print not implemented.");
}

std::string Node::to_string() const {
    throw std::runtime_error("Node print not implemented.");
}

std::string Node::compileToMIPS(const Node *parent_scope) const {
    throw std::runtime_error(this->type + " compileToMIPS not implemented.");
}

void Node::generate_var_maps(Node *parent) {
    std::cerr << this->type << " Node: failed to generate map\n";
}

std::string Node::getDataType() const {
    return data_type;
}

Node* Node::get_intermediate_variable() {
    std::cerr<<"Node: get_intermediate_variable not implemented\n";
    return NULL;
}