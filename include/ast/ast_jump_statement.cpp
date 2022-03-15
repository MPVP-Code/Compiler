#include "ast_assignment.h"
#include "ast_jump_statement.h"
#include "ast_node.h"
#include "ast_variable.h"
#include "../register_allocator.h"

Return::Return(Node* _expression): expression(_expression) {
    this->type = "ReturnExpression";
};

std::string Return::compileToMIPS() const {
    std::string result = "";

    if (expression->type.compare("Variable") == 0) {
        Variable *variable = (Variable*) expression;
        int registerNumber = RegisterAllocator::getRegisterNumberForVariable(variable->getName());
        result = "addu $2, $" + std::to_string(registerNumber) + ", $0";
    } else if (expression->type.compare("Constant") == 0) {
        Constant *constant = (Constant*) expression;
        result = "li $2, " + RegisterAllocator::intToHex(constant->getValue());
    }

    return result;
}
