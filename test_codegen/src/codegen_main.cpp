#include <iostream>
#include "../../include/ast.hpp"

FunctionDeclaration* buildTest2Function() {
    std::vector<Node *> statements;
    Variable *variableB = new Variable("int", "b", true);
    Constant *constant10 = new Constant(10);
    Assign *assignB = new Assign(variableB, constant10);
    statements.push_back(assignB);

    Variable *variableC = new Variable("int", "c", true);
    Constant *constant20 = new Constant(20);
    Assign *assignC = new Assign(variableC, constant20);
    statements.push_back(assignC);

    Addition *additionBAndC = new Addition(variableB, variableC);
    Variable *variableD = new Variable("int", "d", true);
    Assign *assignD = new Assign(variableD, additionBAndC);
    statements.push_back(assignD);

    FunctionDeclaration *function = new FunctionDeclaration("void", "a", statements);
    RegisterAllocator::initCurrentRegister();
    return function;
}

FunctionDeclaration* buildTest3Function() {
    std::vector<Node *> statements;
    Variable *variableB = new Variable("int", "b", true);
    Constant *constant10 = new Constant(10);
    Assign *assignB = new Assign(variableB, constant10);
    statements.push_back(assignB);

    Variable *variableC = new Variable("int", "c", true);
    Constant *constant20 = new Constant(20);
    Assign *assignC = new Assign(variableC, constant20);
    statements.push_back(assignC);

    Addition *additionBAndC = new Addition(variableB, variableC);
    Variable *variableD = new Variable("int", "d", true);
    Assign *assignD = new Assign(variableD, additionBAndC);
    statements.push_back(assignD);

    Identifier *identifierD = new Identifier("d");
    Variable *variableDIdentifier = new Variable ("None", identifierD->identifier, false);
    Return *returnStatement = new Return(variableDIdentifier);
    statements.push_back(returnStatement);

    FunctionDeclaration *function = new FunctionDeclaration("int", "a", statements);
    RegisterAllocator::initCurrentRegister();
    return function;
}

FunctionDeclaration* buildTest4Function() {
    std::vector<Node *> statements;

    Constant *returnedConstant = new Constant(10);
    Return *returnStatement = new Return(returnedConstant);
    statements.push_back(returnStatement);

    FunctionDeclaration *function = new FunctionDeclaration("int", "f", statements);
    RegisterAllocator::initCurrentRegister();
    return function;
}

int main() {
    int testsPassed = 0;
    int testsChecked = 0;

    // Test 1
    /*
     * void a() {
     *  int b = 10;
     * }
     * */

    Variable *variable = new Variable("int", "b", true);
    Constant *constant = new Constant(10);
    Assign *assign = new Assign(variable, constant);
    std::vector<Node *> statements;
    statements.push_back(assign);
    FunctionDeclaration *function = new FunctionDeclaration("void", "a", statements);
    RegisterAllocator::initCurrentRegister();

    std::string test1Out = function->compileToMIPS();
    std::string test1Expected = "a():\nli $2, 0x000a\njr $31\nnop";
    if (test1Out.compare(test1Expected) == 0) {
        testsPassed++;
        std::cout << "Test 1 passed." << std::endl;
    } else {
        std::cout << "Test 1 failed. Expected output: " << test1Expected << " but received: " << test1Out << std::endl;
    }
    testsChecked++;

    // Test 2
    /*
     * void a() {
     *  int b = 10;
     *  int c = 20;
     *  int d = b + c;
     * }
     *
     * */

    FunctionDeclaration* test2Function = buildTest2Function();
    RegisterAllocator::initCurrentRegister();
    RegisterAllocator::reinitRegistersMappingMap();

    std::string test2Out = test2Function->compileToMIPS();
    std::string test2Expected = "a():\nli $2, 0x000a\nli $3, 0x0014\naddu $4, $2, $3\njr $31\nnop";

    if (test2Out.compare(test2Expected) == 0) {
        testsPassed++;
        std::cout << "Test 2 passed." << std::endl;
    } else {
        std::cout << "Test 2 failed. Expected output: " << test2Expected << " but received: " << test2Out << std::endl;
    }
    testsChecked++;

    // Test 3
    /*
     int a() {
        int b = 10;
        int c = 20;
        int d = b + c;
        return d;
     } */
    FunctionDeclaration* test3Function = buildTest3Function();
    RegisterAllocator::initCurrentRegister();
    RegisterAllocator::reinitRegistersMappingMap();

    std::string test3Out = test3Function->compileToMIPS();
    std::string test3Expected = "a():\nli $2, 0x000a\nli $3, 0x0014\naddu $4, $2, $3\naddu $2, $4, $0\njr $31\nnop";

    if (test3Out.compare(test3Expected) == 0) {
        testsPassed++;
        std::cout << "Test 3 passed." << std::endl;
    } else {
        std::cout << "Test 3 failed. Expected output: " << test3Expected << " but received: " << test3Out << std::endl;
    }
    testsChecked++;

    // Test4
    /*
     int f() {
        return 10;
     } */

    FunctionDeclaration* test4Function = buildTest4Function();
    RegisterAllocator::initCurrentRegister();
    RegisterAllocator::reinitRegistersMappingMap();

    std::string test4Out = test4Function->compileToMIPS();
    std::string test4Expected = "f():\nli $2, 0x000a\njr $31\nnop";

    if (test4Out.compare(test4Expected) == 0) {
        testsPassed++;
        std::cout << "Test 4 passed." << std::endl;
    } else {
        std::cout << "Test 4 failed. Expected output: " << test4Expected << " but received: " << test4Out << std::endl;
    }
    testsChecked++;

    std::cout << "Tests passed " << testsPassed << " out of " << testsChecked << std::endl;
}
