//
// Created by michal on 18. 3. 2022.
//
#include "ast_operator.hpp"
#include "../ast.hpp"

BinaryOperator::BinaryOperator(Node *_L, Node *_R) {
    this->type = "BinaryOperator";
    this->L = _L;
    this->R = _R;
}

void BinaryOperator::generate_var_maps(Node *parent) {
    //Generate maps left
    try_replace_variable(this->L, parent);

    //Generate maps right
    try_replace_variable(this->R, parent);

    //Propagate types
    if(L->data_type == "unsigned" || R->data_type == "unsigned"){
        data_type = "unsigned";
    }else {
        data_type = L->data_type;
    }


    //Generate temporary variable
    std::string tmpname = "!tmp" + std::to_string(((Scope*) parent)->tmp_var_counter++);
    this->temp_variable = new Variable(this->data_type, tmpname , true);

    auto scope = (Scope*) parent;
    scope->var_map[tmpname] = this->temp_variable;
}

Node* BinaryOperator::getL() const {
    return L;
};

Node* BinaryOperator::getR() const {
    return R;
};

bool BinaryOperator::isLInt() const {
    return L->data_type.compare("int") == 0;
};

bool BinaryOperator::isRInt() const {
    return R->data_type.compare("int") == 0;
}

Node* BinaryOperator::get_intermediate_variable() {
    return this->temp_variable;
}

std::string BinaryOperator::compileLandRNodesToMIPS(const Node* parent_scope) const {
    std::string result = "";
    std::string LCode = L->compileToMIPS(parent_scope);
    std::string RCode = R->compileToMIPS(parent_scope);
    if (!LCode.empty() && !RCode.empty()) {
        result += LCode + "\n" + RCode;
    } else if (!LCode.empty()) {
        result = LCode;
    } else if (!RCode.empty()) {
        result = RCode;
    }

    return result +  "\n";
}

UnaryOperator::UnaryOperator(Node* _in) {
    this->type = "UnaryOperator";
    this->in = _in;
}

void UnaryOperator::generate_var_maps(Node *parent){
    //Generate maps
    std::cerr << "generating var maps for unary operator"<< std::endl;
    try_replace_variable(this->in, parent);

    //Propagate data types
    data_type = in -> data_type;

    temp_variable = allocate_temp_var(parent, data_type);
}

Node* UnaryOperator::get_intermediate_variable(){
    return this->temp_variable;
}
