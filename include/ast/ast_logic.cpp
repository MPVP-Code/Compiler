#include "ast_logic.hpp"
#include "ast_scope.hpp"
#include "ast_stack.hpp"

LogicAnd::LogicAnd(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->subtype = "LogicAnd";
}

LogicOr::LogicOr(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->subtype = "LogicOr";
}

std::string LogicOr::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    //Resolve wether to use temp variable or actual variable
    if (this->data_type == "int") {
        //Finds temporary / constant/ normal variables in which results have been previously stored
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();

        int id = Global::getIdForLogicOr();
        std::string logicOrLTrueLabel = "$LogicOrLTrue" + std::to_string(id);
        std::string logicOrEndLabel = "$LogicOrEnd" + std::to_string(id);
        std::string logicOrFalseLabel = "$LogicOrFalse" + std::to_string(id);

        result += L->compileToMIPS(parent_scope) + "\n";
        result += load_mapped_variable((Scope*) parent_scope, LVar, "$15") + "\n";
        result += "bne $15, $0, " + logicOrLTrueLabel + "\n";
        result += "nop\n";
        result += R->compileToMIPS(parent_scope) + "\n";
        result += load_mapped_variable((Scope*) parent_scope, RVar, "$14") + "\n";
        result += "beq $14, $0, " + logicOrFalseLabel + "\n";
        result += "nop\n";
        result += logicOrLTrueLabel + ":\n";
        result += "li $13, 1\n";
        result += "b " + logicOrEndLabel + "\n";
        result += "nop\n";
        result += logicOrFalseLabel + ":\n";
        result += "li $13, 0\n";
        result += logicOrEndLabel + ":\n";
        result += store_mapped_variable((Scope*) parent_scope, temp_variable, "$13");
    }
    return result;
}


LogicNot::LogicNot(Node *_source) : UnaryOperator(_source) {
    this->subtype = "LogicNot";
}

std::string LogicNot::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    if (this->data_type == "int") {
        result += in->compileToMIPS(parent_scope);
        Node *inVar = in->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, inVar, "$15") + "\n";
        result += "sltu $15, $15, 1\n";
        result += "andi $15, $15, 0x00ff\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$15");
    }

    return result;
}

LogicEQ::LogicEQ(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->subtype = "Equal";
}

std::string LogicEQ::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    if (this->data_type == "int") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";
        result += "xor $15, $14, $15\n";
        result += "sltu $13, $15, 1\n";
        result += "andi $13, $13, 0x00ff\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    }

    return result;
}

LogicNE::LogicNE(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->subtype = "NotEqual";
}

std::string LogicNE::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    if (this->data_type == "int") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";
        result += "xor $15, $14, $15\n";
        result += "sltu $13, $0, $15\n";
        result += "andi $13, $13, 0x00ff\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    }

    return result;
}

LogicLT::LogicLT(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->subtype = "LessThan";
}

std::string LogicLT::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    if (this->data_type == "int") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$14") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$15") + "\n";
        if (this->data_type == "unsigned") {
            result += "sltu $13, $14, $15\n";
        } else {
            result += "slt $13, $14, $15\n";
        }
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    }

    return result;
}

LogicGT::LogicGT(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->subtype = "GreaterThan";
}

std::string LogicGT::compileToMIPS(const Node *parent_scope) const {
    return compileBinaryOperatorToMIPS(parent_scope, "slt");
}

LogicGE::LogicGE(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->subtype = "GreaterEqual";
}

std::string LogicGE::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    if (this->data_type == "int" || this->data_type == "unsigned") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";
        if (this->data_type == "unsigned") {
            result += "sltu $13, $15, $14\n";
        } else {
            result += "slt $13, $15, $14\n";
        }
        result += "xori $13, $13, 0x1\n";
        result += "andi $13, $13, 0x00ff\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    }

    return result;
}

LogicLE::LogicLE(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->subtype = "LessEqual";
}

std::string LogicLE::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    if (this->data_type == "int" || this->data_type == "unsigned") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";
        if (this->data_type == "unsigned") {
            result += "sltu $13, $14, $15\n";
        } else {
            result += "slt $13, $14, $15\n";
        }
        result += "xori $13, $13, 0x1\n";
        result += "andi $13, $13, 0x00ff\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    }

    return result;
}