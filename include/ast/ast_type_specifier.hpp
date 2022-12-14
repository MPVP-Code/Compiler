#ifndef AST_TYPE_SPECIFIER_HPP
#define AST_TYPE_SPECIFIER_HPP

#include "ast_node.hpp"
#include <vector>

class TypeSpecifier: public Node {
public:
    std::string* typeName;

    TypeSpecifier(std::string* typeName);

    std::string* getTypeName();
};

class EnumElement: public Node {
private:
    std::string name;
    Node* constant;
    int value;
public:
    EnumElement(std::string *_name);

    EnumElement(std::string *_name, Node* _constant);

    std::string getName();

    Node* getConstant();

    int getValue();
};

class Enum: public TypeSpecifier {
private:
    std::string name;
    std::vector<Node*>* elements;
public:
    Enum(std::vector<Node*>* elements);

    Enum(std::string* _name, std::vector<Node*>* elements);

    void generate_var_maps(Node *parent) override;

    virtual std::string compileToMIPS(const Node *parent_scope) const override;

    std::vector<Node*>* getElements();
};

#endif