#include "ast_assignment.hpp"
#include "ast_jump_statement.hpp"
#include "ast_node.hpp"
#include "ast_variable.hpp"
#include "../register_allocator.hpp"
#include "ast_stack.hpp"

Return::Return(Node *_expression) : expression(_expression) {
    this->type = "ReturnExpression";
};

std::string Return::compileToMIPS(const Node *parent_scope) const {
    std::string result = "";

    if (expression->type.compare("Variable") == 0) {
        Variable *variable = (Variable *) expression;
        result = load_mapped_variable((Scope *) parent_scope, variable, "$2") + "\njr $31\nnop";
    } else if (expression->type.compare("Constant") == 0) {
        Constant *constant = (Constant *) expression;
        result = "li $2, " + RegisterAllocator::intToHex(constant->getValue()) + "\njr $31\nnop";
    }

    return result;
}

void Return::generate_var_maps(Node *parent) {
    //Generate map
    try_replace_variable(this->expression, parent);

    //Propagate type
    this->data_type = expression->data_type;
}
