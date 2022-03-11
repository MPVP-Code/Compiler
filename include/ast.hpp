//
// Created by michal on 3. 3. 2022.
//

#ifndef ast_hpp
#define ast_hpp

#include "ast/ast_declaration.hpp"
#include "ast/ast_node.hpp"
#include "ast/ast_func.hpp"
#include "ast/ast_assignment.hpp"
#include "ast/ast_flow_control.hpp"
#include "ast/ast_scope.hpp"
#include "ast/ast_type.hpp"


extern const Node *parseAST();
//extern Node *global_root;

#endif
