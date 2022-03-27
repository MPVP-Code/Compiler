//
// Created by michal on 27. 3. 2022.
//

#ifndef LANGPROC_2021_CW_MPVP_AST_POINTER_HPP
#define LANGPROC_2021_CW_MPVP_AST_POINTER_HPP

#include "ast_operator.hpp"

class AddressOf : public UnaryOperator {
public:

    AddressOf(Node *in);
    std::string compileToMIPS(const Node *parent_scope) const;

};

class Dereference : public UnaryOperator {
public:

    Dereference(Node *in);
    std::string compileToMIPS(const Node *parent_scope) const;

};
#endif //LANGPROC_2021_CW_MPVP_AST_POINTER_HPP
