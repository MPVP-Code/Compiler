//
// Created by michal on 3. 3. 2022.
//

#ifndef AST_HPP
#define AST_HPP

#include "ast/ast_scope.hpp"
#include "ast/ast_node.hpp"
#include "ast/ast_arithmetic.hpp"
#include "ast/ast_assignment.hpp"
#include "ast/ast_flow_control.hpp"
#include "ast/ast_func.hpp"
#include "ast/ast_syntax.hpp"

#include "ast/ast_variable.hpp"

extern const Node *parseAST();

#endif
