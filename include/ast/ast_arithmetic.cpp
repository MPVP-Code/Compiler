#include "ast_arithmetic.hpp"
#include "ast_node.hpp"
#include "ast_operator.hpp"

Addition::Addition(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->subtype = "Addition";
}

std::string Addition::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    //Resolve wether to use temp variable or actual variable
    if (resolve_base_type(this->data_type, (Scope*) parent_scope) == "int") {
        //Finds temporary / constant/ normal variables in which results have been previously stored
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";
        result += "add $13, $14, $15\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    }
    if (resolve_base_type(this->data_type, (Scope*) parent_scope) == "float") {
        //Finds temporary / constant/ normal variables in which results have been previously stored
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$f4") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$f6") + "\n";
        result += "add.s $f2, $f4, $f6\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    }
    return result;
};

Subtraction::Subtraction(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->type = "Subtraction";
}

std::string Subtraction::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    //Resolve wether to use temp variable or actual variable
    if (resolve_base_type(this->data_type, (Scope*) parent_scope) == "int") {
        //Finds temporary / constant/ normal variables in which results have been previously stored
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();

        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";
        result += "sub $13, $15, $14\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    }
    return result;
};


Multiplication::Multiplication(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->type = "Multiplication";
}

std::string Multiplication::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    if (resolve_base_type(this->data_type, (Scope*) parent_scope) == "int") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";
        result += "mult $15, $14\nmflo $13\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    }

    return result;
};


Division::Division(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->type = "Division";
}

std::string Division::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    if (resolve_base_type(this->data_type, (Scope*) parent_scope) == "int") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";
        result += "div $15, $14\nmflo $13\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    }

    return result;
}


Modulo::Modulo(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->type = "Modulo";
}

std::string Modulo::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    if (resolve_base_type(this->data_type, (Scope*) parent_scope) == "int") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";
        result += "div $15, $14\nmfhi $13\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    }

    return result;
}

UnaryMinus::UnaryMinus(Node *in) : UnaryOperator(in) {
    this->subtype = "minus";
}

std::string UnaryMinus::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    //Resolve wether to use temp variable or actual variable
    if (resolve_base_type(this->data_type, (Scope*) parent_scope) == "int") {
        //Finds temporary / constant/ normal variables in which results have been previously stored
        result += in->compileToMIPS(parent_scope);
        Node *InVar = in->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, InVar, "$14") + "\n";
        result += "sub $13, $0, $14\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    }
    return result;
}

PostIncOp::PostIncOp(Node *in) : UnaryOperator(in) {
    this->subtype = "PostInc";
}

std::string PostIncOp::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    //Resolve wether to use temp variable or actual variable
    if (resolve_base_type(this->data_type, (Scope*) parent_scope) == "int") {
        //Finds temporary / constant/ normal variables in which results have been previously stored
        result += in->compileToMIPS(parent_scope);
        Node *InVar = in->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, InVar, "$15") + "\n";
        result += "li $14, 1\n";
        result += "add $13, $14, $15\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    }
    return result;
}

PostDecOp::PostDecOp(Node *in) : UnaryOperator(in) {
    this->subtype = "PostDec";
}

std::string PostDecOp::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    //Resolve wether to use temp variable or actual variable
    if (resolve_base_type(this->data_type, (Scope*) parent_scope) == "int") {
        //Finds temporary / constant/ normal variables in which results have been previously stored
        result += in->compileToMIPS(parent_scope);
        Node *InVar = in->get_intermediate_variable();
        result += "li $15, 1\n";
        result += load_mapped_variable((Scope *) parent_scope, InVar, "$14") + "\n";
        result += "sub $13, $14, $15\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    }
    return result;
}