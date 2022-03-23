//
// Created by michal on 18. 3. 2022.
//

#ifndef AST_OPERATOR_HPP
#define AST_OPERATOR_HPP

#include "ast_node.hpp"

class BinaryOperator : public Node {
public:
    Node *L;
    Node *R;

    BinaryOperator(Node* _L, Node* _R);

    Node* getL() const;

    Node* getR() const;

    bool isLInt() const;

    bool isRInt() const;

    virtual void generate_var_maps(Node *parent) override;
};


class UnaryOperator : public Node {
public:
    Node *in;

    UnaryOperator(Node* _in);

    virtual void generate_var_maps(Node *parent) override;
};

#endif
