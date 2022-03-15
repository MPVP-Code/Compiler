#ifndef AST_RETURN_EXPRESSION_H
#define AST_RETURN_EXPRESSION_H

#include "./ast_node.hpp"

class Return: public Node {
private:
    Node* expression;
public:
    Return(Node* _expression): expression(_expression) {
        this->type = "ReturnExpression";
    }

    virtual std::string compileToMIPS() const {
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
};

#endif