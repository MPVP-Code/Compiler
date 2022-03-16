#include "ast_assignment.hpp"
#include "ast_jump_statement.hpp"
#include "ast_node.hpp"
#include "ast_variable.hpp"
#include "../register_allocator.hpp"

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
