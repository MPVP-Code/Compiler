//
// Created by michal on 3. 3. 2022.
//

#ifndef AST_HPP
#define AST_HPP

#include "ast/ast_scope.h"
#include "ast/ast_node.cpp"
#include "ast/ast_arithmetic.cpp"
#include "ast/ast_assignment.cpp"
//#include "ast/ast_flow_control.hpp"
#include "ast/ast_func.h"
#include "ast/ast_syntax.cpp"
#include "ast/ast_jump_statement.hpp"
#include "ast/ast_variable.hpp"

extern const Node *parseAST();

#endif
