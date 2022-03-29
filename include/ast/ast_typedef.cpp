#include "ast_typedef.hpp"
#include "ast_scope.hpp"
#include "ast_stack.hpp"

TypeDef::TypeDef(std::string _basicType, std::string _newType): basicType(_basicType), newType(_newType) {
    this->type = "TypeDef";
}

std::string TypeDef::compileToMIPS(const Node *parent_scope) const {
    return "";
}

void TypeDef::generate_var_maps(Node *parent) {
        auto scope = (Scope*) parent;
        int size = resolve_variable_size(basicType,scope );
        scope->type_map[newType] = new Variable_type(newType, basicType, size);

//        auto basicType = parent_scope->type_map.find(typeDef->getBasicType());
//        if (basicType != parentScope->type_map.end()) {
//            parentScope->type_map[typeDef->getBasicType()] = basicType->second;
//

}

//std::string TypeDef::compileToMIPS(const Node *parent_scope) const {
//    return "";
//}
//
//std::string TypeDef::getBasicType() const {
//    return this->basicType;
//}
//
//std::string TypeDef::getNewType() const {
//    return this->newType;
//}