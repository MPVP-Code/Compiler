#include "ast_arithmetic.hpp"
#include "ast_node.hpp"
#include "ast_operator.hpp"

Addition::Addition(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->subtype = "Addition";
}

std::string Addition::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    //Resolve wether to use temp variable or actual variable
    std::string basicDataType = resolve_base_codepath(this->data_type, (Scope*) parent_scope);

    if (basicDataType == "int") {
        //Finds temporary / constant/ normal variables in which results have been previously stored
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();

        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";

        //Pointer arithmetic fix
        if (L->data_type.at(L->data_type.size()-1) == '*' ^ R->data_type.at(R->data_type.size()-1) == '*') {
            if (L->data_type.at(L->data_type.size() - 1) == '*') {
                result += "sll $14, $14, " + std::to_string(get_log_ptr_element(L->data_type, (Scope *) parent_scope)) +   " # Pointer arithmetic bodge\n";
            }
            if (R->data_type.at(R->data_type.size() - 1) == '*') {
                result += "sll $15, $15, " + std::to_string(get_log_ptr_element(R->data_type, (Scope *) parent_scope)) +  "\n";
            }
        }

        result += "add $13, $14, $15\n";

        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    } else if (basicDataType == "float") {
        //Finds temporary / constant/ normal variables in which results have been previously stored
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";
        result += "mtc1 $15, $f4\n";
        result += "mtc1 $14, $f6\n";
        result += "add.s $f2, $f4, $f6\n";
        result += "mfc1 $13, $f2\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    } else if (basicDataType == "double") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable_coprocessor((Scope *) parent_scope, LVar, "$f6") + "\n";
        result += load_mapped_variable_coprocessor((Scope *) parent_scope, RVar, "$f4") + "\n";
        result += "add.d $f0, $f4, $f6\n";
    }
    return result;
};

Subtraction::Subtraction(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->type = "Subtraction";
}

std::string Subtraction::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    std::string basicDataType = resolve_base_codepath(this->data_type, (Scope*) parent_scope);
    //Resolve wether to use temp variable or actual variable
    if (basicDataType == "int") {
        //Finds temporary / constant/ normal variables in which results have been previously stored
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();

        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";

        //Pointer arithmetic fix
        if (L->data_type.at(L->data_type.size()-1) == '*' ^ R->data_type.at(R->data_type.size()-1) == '*') {
            if (L->data_type.at(L->data_type.size() - 1) == '*') {
                result += "sll $14, $14, " + std::to_string(get_log_ptr_element(L->data_type, (Scope *) parent_scope)) +   " # Pointer arithmetic bodge\n";
            }
            if (R->data_type.at(R->data_type.size() - 1) == '*') {
                result += "sll $15, $15, " + std::to_string(get_log_ptr_element(R->data_type, (Scope *) parent_scope)) +  "\n";
            }
        }

        result += "sub $13, $15, $14\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    } else if (basicDataType == "float") { /*might cause segmentation faults*/
        //Finds temporary / constant/ normal variables in which results have been previously stored
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";
        result += "mtc1 $15, $f4\n";
        result += "mtc1 $14, $f6\n";
        result += "sub.s $f2, $f4, $f6\n";
        result += "mfc1 $13, $f2\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    } else if (basicDataType == "double") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable_coprocessor((Scope *) parent_scope, LVar, "$f4") + "\n";
        result += load_mapped_variable_coprocessor((Scope *) parent_scope, RVar, "$f6") + "\n";
        result += "sub.d $f0, $f4, $f6\n";
    }
    return result;
};


Multiplication::Multiplication(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->type = "Multiplication";
}

std::string Multiplication::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    std::string basicDataType = resolve_base_codepath(this->data_type, (Scope*) parent_scope);

    if (basicDataType == "int") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";
        result += "mult $15, $14\nmflo $13\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    } else if (basicDataType == "float") {
        //Finds temporary / constant/ normal variables in which results have been previously stored
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";
        result += "mtc1 $15, $f4\n";
        result += "mtc1 $14, $f6\n";
        result += "mul.s $f2, $f4, $f6\n";
        result += "mfc1 $13, $f2\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    } else if (basicDataType == "double") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable_coprocessor((Scope *) parent_scope, LVar, "$f6") + "\n";
        result += load_mapped_variable_coprocessor((Scope *) parent_scope, RVar, "$f4") + "\n";
        result += "mul.d $f0, $f4, $f6\n";
    }

    return result;
};


Division::Division(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->type = "Division";
}

std::string Division::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    std::string basicDataType = resolve_base_codepath(this->data_type, (Scope*) parent_scope);

    if (basicDataType == "int") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";
        result += "div $15, $14\nmflo $13\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    } else if (basicDataType == "float") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, LVar, "$15") + "\n";
        result += load_mapped_variable((Scope *) parent_scope, RVar, "$14") + "\n";
        result += "mtc1 $15, $f4\n";
        result += "mtc1 $14, $f6\n";
        result += "div.s $f2, $f4, $f6\n";
        result += "mfc1 $13, $f2\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
    } else if (basicDataType == "double") {
        result += compileLandRNodesToMIPS(parent_scope);
        Node *LVar = L->get_intermediate_variable();
        Node *RVar = R->get_intermediate_variable();
        result += load_mapped_variable_coprocessor((Scope *) parent_scope, LVar, "$f4") + "\n";
        result += load_mapped_variable_coprocessor((Scope *) parent_scope, RVar, "$f6") + "\n";
        result += "div.d $f0, $f4, $f6\n";
    }

    return result;
}


Modulo::Modulo(Node *_L, Node *_R) : BinaryOperator(_L, _R) {
    this->type = "Modulo";
}

std::string Modulo::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    std::string basicDataType = resolve_base_codepath(this->data_type, (Scope*) parent_scope);

    if (basicDataType == "int") {
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
    std::string basicDataType = resolve_base_codepath(this->data_type, (Scope*) parent_scope);

    //Resolve wether to use temp variable or actual variable
    if (basicDataType == "int") {
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
    std::string basicDataType = resolve_base_codepath(this->data_type, (Scope*) parent_scope);
    //Resolve wether to use temp variable or actual variable
    if (basicDataType == "int") {

        //Finds temporary / constant/ normal variables in which results have been previously stored
        result += in->compileToMIPS(parent_scope);
        Node *InVar = in->get_intermediate_variable();
        result += load_mapped_variable((Scope *) parent_scope, InVar, "$14") + "\n";
        result += "li $15, 1\n";

        //Pointer arithmetic fix
        if (in->data_type.at(in->data_type.size()-1) == '*' ) {
            result += "sll $15, $15, " + std::to_string(get_log_ptr_element(in->data_type, (Scope *) parent_scope)) +   " # Pointer arithmetic bodge\n";
        }

        result += "add $13, $14, $15\n";
        result += store_mapped_variable((Scope *) parent_scope, InVar, "$13");
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$14");
    }
    return result;
}

std::string PreIncOp::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    std::string basicDataType = resolve_base_codepath(this->data_type, (Scope*) parent_scope);
    //Resolve wether to use temp variable or actual variable
    if (basicDataType == "int") {

        //Finds temporary / constant/ normal variables in which results have been previously stored
        result += in->compileToMIPS(parent_scope);
        Node *InVar = in->get_intermediate_variable();
        result += "li $15, 1\n";
        result += load_mapped_variable((Scope *) parent_scope, InVar, "$14") + "\n";

        //Pointer arithmetic fix
        if (in->data_type.at(in->data_type.size()-1) == '*' ) {
            result += "sll $15, $15, " + std::to_string(get_log_ptr_element(in->data_type, (Scope *) parent_scope)) +   " # Pointer arithmetic bodge\n";
        }

        result += "add $13, $14, $15\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
        result += store_mapped_variable((Scope *) parent_scope, InVar, "$13");
    }
    return result;
}

PostDecOp::PostDecOp(Node *in) : UnaryOperator(in) {
    this->subtype = "PostDec";
}

std::string PostDecOp::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    std::string basicDataType = resolve_base_codepath(this->data_type, (Scope*) parent_scope);
    //Resolve wether to use temp variable or actual variable
    if (basicDataType == "int") {
        //Finds temporary / constant/ normal variables in which results have been previously stored
        result += in->compileToMIPS(parent_scope);
        Node *InVar = in->get_intermediate_variable();
        result += "li $15, 1\n";
        result += load_mapped_variable((Scope *) parent_scope, InVar, "$14") + "\n";

        //Pointer arithmetic fix
        if (in->data_type.at(in->data_type.size()-1) == '*' ) {
            result += "sll $15, $15, " + std::to_string(get_log_ptr_element(in->data_type, (Scope *) parent_scope)) +   " # Pointer arithmetic bodge\n";
        }

        result += "sub $13, $14, $15\n";
        result += store_mapped_variable((Scope *) parent_scope, InVar, "$13");
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$14");
    }
    return result;
}

PreDecOp::PreDecOp(Node *in) : UnaryOperator(in) {
    this->subtype = "PreDec";
}

std::string PreDecOp::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    std::string basicDataType = resolve_base_codepath(this->data_type, (Scope*) parent_scope);
    //Resolve wether to use temp variable or actual variable
    if (basicDataType == "int") {
        //Finds temporary / constant/ normal variables in which results have been previously stored
        result += in->compileToMIPS(parent_scope);
        Node *InVar = in->get_intermediate_variable();
        result += "li $15, 1\n";
        result += load_mapped_variable((Scope *) parent_scope, InVar, "$14") + "\n";

        //Pointer arithmetic fix
        if (in->data_type.at(in->data_type.size()-1) == '*' ) {
            result += "sll $15, $15, " + std::to_string(get_log_ptr_element(in->data_type, (Scope *) parent_scope)) +   " # Pointer arithmetic bodge\n";
        }
        result += "sub $13, $14, $15\n";
        result += store_mapped_variable((Scope *) parent_scope, temp_variable, "$13");
        result += store_mapped_variable((Scope *) parent_scope, InVar, "$13");
    }
    return result;
}


PreIncOp::PreIncOp(Node *in) : UnaryOperator(in) {
    this->subtype = "PreInc";
}

