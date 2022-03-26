#include "ast_logic.hpp"
#include "ast_scope.hpp"
#include "ast_stack.hpp"

LogicAnd::LogicAnd(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "LogicAnd";
}

LogicOr::LogicOr(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "LogicOr";
}
LogicNot::LogicNot(Node *_source) : UnaryOperator(_source){
    this->subtype = "LogicNot";
}
LogicEQ::LogicEQ(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "Equal";
}
LogicNE::LogicNE(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "NotEqual";
}
LogicLT::LogicLT(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "LessThan";
}

std::string LogicLT::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    if (this->data_type == "int") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope*) parent_scope, LVar, "$14") + "\n";
        result += load_mapped_variable((Scope*) parent_scope, RVar, "$15") + "\n";
        result += "slt $13, $14, $15\n";
        result += store_mapped_variable((Scope*) parent_scope, temp_variable, "$13");
    }

    return result;
}

LogicGT::LogicGT(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "GreaterThan";
}

std::string LogicGT::compileToMIPS(const Node *parent_scope) const {
    return compileBinaryOperatorToMIPS(parent_scope, "slt");
}

LogicGE::LogicGE(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "GreaterEqual";
}

LogicLE::LogicLE(Node *_L, Node *_R) : BinaryOperator(_L, _R){
    this->subtype = "LessEqual";
}

