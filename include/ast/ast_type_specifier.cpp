#include "ast_type_specifier.hpp"
#include "ast_scope.hpp"

TypeSpecifier::TypeSpecifier(std::string *_typeName) : typeName(_typeName) {
    this->type = "TypeSpecifier";
}

std::string *TypeSpecifier::getTypeName() {
    return this->typeName;
}

EnumElement::EnumElement(std::string* _name): name(*_name) {
    this->type = "EnumElement";
}

EnumElement::EnumElement(std::string* _name, Node* _value): name(*_name), value(_value) {
    this->type = "EnumElement";
}

std::string EnumElement::getName() {
    return name;
}

Node* EnumElement::getValue() {
    return value;
}

Enum::Enum(std::vector<Node *> *_elements) : TypeSpecifier(new std::string("enum")), elements(_elements) {
    this->subtype = "Enum";
}

Enum::Enum(std::string *_name, std::vector<Node*> *_elements) :
        TypeSpecifier(new std::string("enum")), name(*_name), elements(_elements) {
    this->subtype = "Enum";
}

void Enum::generate_var_maps(Node *parent) {
    return;
}

std::string Enum::compileToMIPS(const Node *parent_scope) const {
    return "";
}

std::vector<Node*>* Enum::getElements() {
    return elements;
}