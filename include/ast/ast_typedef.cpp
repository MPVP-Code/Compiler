#include "ast_typedef.hpp"
#include "ast_scope.hpp"

TypeDef::TypeDef(std::string _basicType, std::string _newType): basicType(_basicType), newType(_newType) {
    this->type = "TypeDef";
}

std::string TypeDef::compileToMIPS(const Node *parent_scope) const {
    return "";
}

std::string TypeDef::getBasicType() const {
    return this->basicType;
}

std::string TypeDef::getNewType() const {
    return this->newType;
}