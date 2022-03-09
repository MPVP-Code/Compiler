#ifndef AST_DECLARATION_H
#define AST_DECLARATION_H


#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "ast_node.hpp"

class Declarator : Node {
};

class DirectDeclarator : Declarator {
};

class DeclarationSpecifiers : Node {

};

class Initializer : Node {

};

class InitDeclaratorList : Node {

};

class UnaryExpression: Initializer {};

class InitDeclarator : public Node {
private:
    Declarator *declarator;
    Initializer *initializer;
};

class Identifier : Node {
private:
    const std::string *identifier;
public:
    Identifier(const std::string *_identifier) : identifier(_identifier) {}

    virtual std::string to_string() const {
        return "Identifier => (" + *this->identifier + ")";
    }
};

class Declaration : Node {
private:
    DeclarationSpecifiers *declarationSpecifier;
    InitDeclaratorList *initDeclaratorList;

public:
    Declaration(DeclarationSpecifiers *_declarationSpecifier, InitDeclaratorList *_initDeclaratorList)
            : declarationSpecifier(_declarationSpecifier), initDeclaratorList(_initDeclaratorList) {
        this->type = "declaration";
    }
};

#endif
