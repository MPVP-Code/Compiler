//
// Created by michal on 3. 3. 2022.
//

#ifndef AST_HPP
#define AST_HPP

#include "ast/ast_scope.h"
#include "ast/ast_node.h"
#include "ast/ast_arithmetic.h"
#include "ast/ast_assignment.h"
//#include "ast/ast_flow_control.hpp"
#include "ast/ast_func.h"
#include "ast/ast_syntax.h"
#include "ast/ast_jump_statement.h"
#include "ast/ast_variable.h"

extern const Node *parseAST();

#endif
