#include "ast_assignment.hpp"
#include "ast_jump_statement.hpp"
#include "ast_node.hpp"
#include "ast_variable.hpp"
#include "ast_stack.hpp"

Return::Return(Node *_expression) : expression(_expression) {
    this->type = "ReturnExpression";
};

std::string Return::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";
    if (expression->data_type == "int") {
        result += load_mapped_variable((Scope *) parent_scope, expression, "$v0") + "\n";
        result += "\njr $31\nnop\n";
    }

    return result;
}

void Return::generate_var_maps(Node *parent) {
    //Generate map
    try_replace_variable(this->expression, parent);

    //Propagate type
    this->data_type = expression->data_type;
}
