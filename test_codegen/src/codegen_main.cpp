#include <iostream>
#include "../../include/ast.hpp"

int main() {
    int testsPassed = 0;
    int testsChecked = 0;
    Variable *variable = new Variable("int", "b");
    Constant *constant = new Constant(10);
    Assign *assign = new Assign(variable, constant);
    std::vector<Node *> statements;
    statements.push_back(assign);
    Function *function = new Function("void", "a", statements);

    std::string test1Out = function->compileToMIPS();
    std::string test1Expected = "a():\nli $2, 0x000a";
    if (test1Out.compare(test1Expected) == 0) {
        testsPassed++;
        std::cout << "Test 1 passed." << std::endl;
    } else {
        std::cout << "Test 1 failed. Expected output: " << test1Expected << " but received: " << test1Out << std::endl;
    }
    testsChecked++;

    std::cout << "Tests passed " << testsPassed << " out of " << testsChecked << std::endl;
}
