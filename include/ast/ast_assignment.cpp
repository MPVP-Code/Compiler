#include "ast_variable.hpp"
#include "ast_scope.hpp"
#include "ast_node.hpp"
#include "ast_assignment.hpp"
#include "ast_stack.hpp"
#include "ast_operator.hpp"
#include <string>


Constant::Constant(int _value) : value(_value) {
    this->type = "Constant";
    this->data_type = "int";
}

int Constant::getValue() {
    return this->value;
}

void Constant::generate_var_maps(Node *parent) {
    const_var = allocate_temp_var(parent, data_type);

}

Node* Constant::get_intermediate_variable(){
    return const_var;
}

std::string Constant::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    if (resolve_base_codepath(data_type, (Scope*)parent_scope) == "int") {

        std::string hexValue = intToHex(value);
        result += "li $15, " + hexValue + "\n";

        result += store_mapped_variable((Scope *) parent_scope, const_var, "$15");
    }
    return result;
}

ConstantFloat::ConstantFloat(float _value): value(_value) {
    this->type = "Constant";
    this->data_type = "float";
}

float ConstantFloat::getValue() {
    return this->value;
}

Variable* ConstantFloat::getConstVar() {
    return this->const_var;
}

void ConstantFloat::generate_var_maps(Node *parent) {
    const_var = allocate_temp_var(parent, data_type);
}

std::string ConstantFloat::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    if (resolve_base_type(data_type, (Scope*)parent_scope) == "float") {
        std::string binaryValue = convertFloatToBinary(value);
        result = "li $15, " + binaryValue + "\n";
        result += store_mapped_variable((Scope *) parent_scope, const_var, "$15");
    }
    return result;
}

Node* ConstantFloat::get_intermediate_variable() {
    return const_var;
}

Assign::Assign(Node *_destination, Node *_source) : destination(_destination), source(_source) {
    this->type = "Assign";
}

void Assign::generate_var_maps(Node *parent) {

    //Destination var mapping
    try_replace_variable(destination, parent);

    //Source varmapping
    try_replace_variable(source, parent);

    //type propagation
    this->data_type = destination->data_type;

    //Try set pointer size from string literal
    if(this->source->type == "Constant" && this->source->subtype == "StringLiteral"){
        int size = ((StringLiteral* )this->source)->str_value.size() +1;
        if(size > ((Variable*) this->destination)->array_size) {
            ((Variable *) this->destination)->array_size = size;
        }
    }
}

std::string Assign::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    //Calculate Rvalue
    result += source->compileToMIPS(parent_scope);
    Node *src_var = source->get_intermediate_variable();


    if(source->type == "Constant" && source->subtype == "StringLiteral" ){
        //Array load for raw pointers
        result += load_mapped_variable((Scope *) parent_scope, destination->get_intermediate_variable(), "$13");
        result += copy_str_literal("$13", ((StringLiteral*) source)->str_value);

    }else if (destination->type == "Variable") {
        result += load_mapped_variable((Scope *) parent_scope, src_var, "$14");
        result += store_mapped_variable((Scope *) parent_scope, destination, "$14");

    }else if (destination->type == "UnaryOperator" && destination->subtype == "Dereference"){

        //So not dereference, just grab address
        result += ((UnaryOperator *)destination)->in->compileToMIPS(parent_scope);

        //Array load for strings from dereferenced pointer
        if(source->type == "Constant" && source->subtype == "StringLiteral" ){

            result += load_mapped_variable((Scope *) parent_scope, ((UnaryOperator *) destination)->in->get_intermediate_variable(), "$13");
            result += copy_str_literal("$13", ((StringLiteral*) source)->str_value);

        }else {
            //Load Rvalue
            result += load_mapped_variable((Scope *) parent_scope, src_var, "$14");

            //Load pointer address
            result += load_mapped_variable((Scope *) parent_scope, ((UnaryOperator *) destination)->in->get_intermediate_variable(), "$13");

            //Store at pointer address
            result += store_raw_variable((Scope *) parent_scope, "$13", "$14", destination->data_type);
        }

    }
    return result;
};


StringLiteral::StringLiteral(int value, std::string _in) : Constant(value) {
    this->type = "Constant";
    this->subtype = "StringLiteral";
    //Strip quotes
    std::string intermediate = _in.substr(1, _in.size()-2);
    std::string out = "";

    //and resolve escape characters
    int is_escaped = 0;
    for (char c : intermediate){
        if (c == '\\' && !is_escaped){
            is_escaped = 1;
        }else if (is_escaped){
            switch (c) {
                case 'a' :{
                    out+= '\a';
                    break;
                }
                case 'b' :{
                    out+= '\b';
                    break;
                }
                case 'f' :{
                    out+= '\f';
                    break;
                }
                case 'n' :{
                    out+= '\n';
                    break;
                }case 'r' :{
                    out+= '\r';
                    break;
                }
                case 't' :{
                    out+= '\t';
                    break;
                }
                case 'v' :{
                    out+= '\v';
                    break;
                }
                case '\\' :{
                    out+= '\\';
                    break;
                }case '\'' :{
                    out+= '\'';
                    break;
                }
                case '\"' :{
                    out+= '\"';
                    break;
                }
                case '\?' :{
                    out+= '\?';
                    break;
                }

            }
            is_escaped--;
        }
        else{
            out+=c;
        }
    }
    str_value = out;
}

void StringLiteral::generate_var_maps(Node *parent) {
    const_var = allocate_temp_var(parent, data_type);
    const_var->array_size = this->str_value.size()+1;
    const_var->data_type = "char*";
}

std::string StringLiteral::compileToMIPS(const Node *parent_scope) const {
    std::string result ="# Stack string pointer generation\n";
    result += "addiu $13, $sp, " + std::to_string(resolve_variable_offset(const_var->name, (Scope*) parent_scope)+4) + "\n";
    result+= store_mapped_variable((Scope *) parent_scope, const_var, "$13");
    result += "#Stack string load (Sometimes redundant)\n";
    result += copy_str_literal("$13", str_value);
    return result;
}
