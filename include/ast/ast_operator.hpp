//
// Created by michal on 18. 3. 2022.
//

#ifndef AST_OPERATOR_HPP
#define AST_OPERATOR_HPP

#include "ast_node.hpp"
#include "ast_variable.hpp"

class BinaryOperator : public Node {
public:
    Node *L;
    Node *R;

    Variable* temp_variable;

    BinaryOperator(Node* _L, Node* _R);

    Node* getL() const;

    Node* getR() const;

    bool isLInt() const;

    bool isRInt() const;

    virtual void generate_var_maps(Node *parent) override;

    Node* get_intermediate_variable() override;

    std::string compileLandRNodesToMIPS(const Node* parent_scope) const;
};


class UnaryOperator : public Node {
public:
    Node *in;

    Variable* temp_variable;

    UnaryOperator(Node* _in);

    virtual void generate_var_maps(Node *parent) override;

    Node* get_intermediate_variable() override;
};

#endif
