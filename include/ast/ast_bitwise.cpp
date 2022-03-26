#include "ast_bitwise.hpp"
#include "ast_scope.hpp"
#include "ast_stack.hpp"

BitAnd::BitAnd(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->type = "BitAnd";
}

std::string BitAnd::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    result += compileLandRNodesToMIPS(parent_scope);
    Node *LVar = L->get_intermediate_variable();
    Node *RVar = R->get_intermediate_variable();
    result += load_mapped_variable((Scope*) parent_scope, LVar, "$14") + "\n";
    result += load_mapped_variable((Scope*) parent_scope, RVar, "$15") + "\n";
    result += "and $13, $14, $15\n";
    result += store_mapped_variable((Scope*) parent_scope, temp_variable, "$13");

    return result;
}

BitOr::BitOr(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->type = "BitOr";
}

std::string BitOr::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    result += compileLandRNodesToMIPS(parent_scope);
    Node *LVar = L->get_intermediate_variable();
    Node *RVar = R->get_intermediate_variable();
    result += load_mapped_variable((Scope*) parent_scope, LVar, "$14") + "\n";
    result += load_mapped_variable((Scope*) parent_scope, RVar, "$15") + "\n";
    result += "or $13, $14, $15\n";
    result += store_mapped_variable((Scope*) parent_scope, temp_variable, "$13");

    return result;
}

BitXor::BitXor(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->type = "BitXor";
}

std::string BitXor::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    result += compileLandRNodesToMIPS(parent_scope);
    Node *LVar = L->get_intermediate_variable();
    Node *RVar = R->get_intermediate_variable();
    result += load_mapped_variable((Scope*) parent_scope, LVar, "$14") + "\n";
    result += load_mapped_variable((Scope*) parent_scope, RVar, "$15") + "\n";
    result += "xor $13, $14, $15\n";
    result += store_mapped_variable((Scope*) parent_scope, temp_variable, "$13");

    return result;
}

BitNot::BitNot(Node *_in) : UnaryOperator(_in){
    this->type = "BitNot";
}

std::string BitNot::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    result += in->compileToMIPS(parent_scope);
    Node *InVar = in->get_intermediate_variable();
    result += load_mapped_variable((Scope*) parent_scope, InVar, "$14") + "\n";
    result += "nor $13, $14, $14\n";
    result += store_mapped_variable((Scope*) parent_scope, temp_variable, "$13");

    return result;
}

BitASL::BitASL(Node *_L, Node* _R) : BinaryOperator(_L, _R){
    this->subtype = "ASL";
}

std::string BitASL::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope*) parent_scope, LVar, "$14") + "\n";
        result += load_mapped_variable((Scope*) parent_scope, RVar, "$15") + "\n";
        result += "sllv $13, $14, $15\n";
        result += store_mapped_variable((Scope*) parent_scope, temp_variable, "$13");

    return result;
}

BitASR::BitASR(Node *_L, Node* _R) : BinaryOperator(_L, _R){
    this->subtype = "ASR";
}

std::string BitASR::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    if (this->data_type == "int") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope*) parent_scope, LVar, "$14") + "\n";
        result += load_mapped_variable((Scope*) parent_scope, RVar, "$15") + "\n";
        result += "srav $13, $14, $15\n";
        result += store_mapped_variable((Scope*) parent_scope, temp_variable, "$13");

    }else if (this->data_type == "unsigned") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope*) parent_scope, LVar, "$14") + "\n";
        result += load_mapped_variable((Scope*) parent_scope, RVar, "$15") + "\n";
        result += "srlv $13, $14, $15\n";
        result += store_mapped_variable((Scope*) parent_scope, temp_variable, "$13");
    }

    return result;
}