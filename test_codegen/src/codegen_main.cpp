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

FunctionDeclaration* buildTest5Function() {
    std::vector<Node *> statements;

    Variable *variable = new Variable("int", "x", false);
    statements.push_back(variable);

    Constant *constant10 = new Constant(10);
    Assign *assignVar = new Assign(variable, constant10);
    statements.push_back(assignVar);

    Return *returnStatement = new Return(variable);
    statements.push_back(returnStatement);

    FunctionDeclaration *function = new FunctionDeclaration("int", "f", statements);
    return function;
}

FunctionDeclaration* buildTest6Function() {
    std::vector<Node *> statements;
    std::vector<Node *> trueStatements;

    Constant *constant11 = new Constant(11);
    Return *returnTrue = new Return(constant11);
    trueStatements.push_back(returnTrue);

    Constant *condition = new Constant(0);

    If *ifStatement = new If(condition, &trueStatements, nullptr);
    statements.push_back(ifStatement);

    Constant *constant10 = new Constant(10);
    Return *returnFalse = new Return(constant10);
    statements.push_back(returnFalse);

    FunctionDeclaration *function = new FunctionDeclaration("int", "f", statements);
    return function;
}

FunctionDeclaration* buildTest7Function() {
    std::vector<Node *> statements;
    std::vector<Node *>* trueStatements = new std::vector<Node*>;

    Constant *constant11 = new Constant(11);
    Return *returnTrue = new Return(constant11);
    trueStatements->push_back(returnTrue);

    Constant *condition = new Constant(1);

    If *ifStatement = new If(condition, trueStatements, nullptr);
    statements.push_back(ifStatement);

    Constant *constant10 = new Constant(10);
    Return *returnStatement = new Return(constant10);
    statements.push_back(returnStatement);

    FunctionDeclaration *function = new FunctionDeclaration("int", "f", statements);
    return function;
}

FunctionDeclaration* buildTest8Function() {
    std::vector<Node *> statements;
    std::vector<Node *>* trueStatements = new std::vector<Node*>;
    std::vector<Node *>* falseStatements = new std::vector<Node*>;

    Constant *constant11 = new Constant(11);
    Return *returnTrue = new Return(constant11);
    trueStatements->push_back(returnTrue);

    Constant *condition = new Constant(0);

    Constant *constant10 = new Constant(10);
    Return *returnFalse = new Return(constant10);
    falseStatements->push_back(returnFalse);

    If *ifStatement = new If(condition, trueStatements, falseStatements);
    statements.push_back(ifStatement);

    FunctionDeclaration *function = new FunctionDeclaration("int", "f", statements);
    return function;
}

FunctionDeclaration* buildTest9Function() {
    std::vector<Node*> statements;
    std::vector<Node*>* whileStatements = new std::vector<Node*>;

    Constant *constant0 = new Constant(0);
    While *whileStatement = new While(constant0, whileStatements);
    statements.push_back(whileStatement);

    Constant *returnConstant = new Constant(19937);
    Return *returnStatement = new Return(returnConstant);
    statements.push_back(returnStatement);

    FunctionDeclaration *function = new FunctionDeclaration("int", "f", statements);
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
    std::string test1Expected = "a:\n.set noreorder\nli $2, 0x000a\njr $31\nnop";
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
    std::string test2Expected = "a:\n.set noreorder\nli $2, 0x000a\nli $3, 0x0014\naddu $4, $2, $3\njr $31\nnop";

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
    std::string test3Expected = "a:\n.set noreorder\nli $2, 0x000a\nli $3, 0x0014\naddu $4, $2, $3\naddu $2, $4, $0\njr $31\nnop";

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
    std::string test4Expected = "f:\n.set noreorder\nli $2, 0x000a\njr $31\nnop";

    if (test4Out.compare(test4Expected) == 0) {
        testsPassed++;
        std::cout << "Test 4 passed." << std::endl;
    } else {
        std::cout << "Test 4 failed. Expected output: " << test4Expected << " but received: " << test4Out << std::endl;
    }
    testsChecked++;

    // Test 5
    /*
     int ffff() {
        int x;
        x=10;
        return x;
     }
     */
    RegisterAllocator::initCurrentRegister();
    RegisterAllocator::reinitRegistersMappingMap();

    FunctionDeclaration* test5Function = buildTest5Function();
    std::string test5Out = test5Function->compileToMIPS();
    std::string test5Expected = "f:\n.set noreorder\nli $2, 0x0000\nli $2, 0x000a\naddu $2, $2, $0\njr $31\nnop";
    if (test5Out.compare(test5Expected) == 0) {
        testsPassed++;
        std::cout << "Test 5 passed." << std::endl;
    } else {
        std::cout << "Test 5 failed. Expected output: " << test5Expected << " but received: " << test5Out << std::endl;
    }
    testsChecked++;

    //Test 6
    /*
    int f()
    {
        if(0){
            return 11;
        }
        return 10;
    } */
    RegisterAllocator::initCurrentRegister();
    RegisterAllocator::reinitRegistersMappingMap();

    FunctionDeclaration* test6Function = buildTest6Function();
    std::string test6Out = test6Function->compileToMIPS();
    std::string test6Expected = "f:\n.set noreorder\nli $2, 0x000a\njr $31\nnop";

    if (test6Out.compare(test6Expected) == 0) {
        testsPassed++;
        std::cout << "Test 6 passed." << std::endl;
    } else {
        std::cout << "Test 6 failed. Expected output: " << test6Expected << " but received: " << test6Out << std::endl;
    }

    testsChecked++;

    // Test 7
    /*
    int f()
    {
        if(1){
            return 11;
        }
        return 10;
    }
    */

    RegisterAllocator::initCurrentRegister();
    RegisterAllocator::reinitRegistersMappingMap();

    FunctionDeclaration* test7Function = buildTest7Function();
    std::string test7Out = test7Function->compileToMIPS();
    std::string test7Expected = "f:\n.set noreorder\nli $2, 0x000b\njr $31\nnop\nli $2, 0x000a\njr $31\nnop";

    if (test7Out.compare(test7Expected) == 0) {
        testsPassed++;
        std::cout << "Test 7 passed." << std::endl;
    } else {
        std::cout << "Test 7 failed. Expected output: " << test7Expected << " but received: " << test7Out << std::endl;
    }
    testsChecked++;

    // Test 8
    /*
     int f()
{
    if(0){
        return 11;
    }else{
        return 10;
    }
}*/
    FunctionDeclaration* test8Function = buildTest8Function();
    std::string test8Out = test8Function->compileToMIPS();
    std::string test8Expected = "f:\n.set noreorder\nli $2, 0x000a\njr $31\nnop\njr $31\nnop"; // Because of the fact that the function does not know its context

    if (test8Out.compare(test8Expected) == 0) {
        testsPassed++;
        std::cout << "Test 8 passed." << std::endl;
    } else {
        std::cout << "Test 8 failed. Expected output: " << test8Expected << " but received: " << test8Out << std::endl;
    }
    testsChecked++;

    // Test 9
    /*
    int f()
    {
        while(0){

        }
        return 19937;
    }
     */
    FunctionDeclaration* test9Function = buildTest9Function();
    std::string test9Out = test9Function->compileToMIPS();
    std::string test9Expected = "f:\n.set noreorder\nli $2, 0x4e1\njr $31\nnop";

    if (test8Out.compare(test8Expected) == 0) {
        testsPassed++;
        std::cout << "Test 9 passed." << std::endl;
    } else {
        std::cout << "Test 9 failed. Expected output: " << test8Expected << " but received: " << test8Out << std::endl;
    }
    testsChecked++;

    std::cout << "Tests passed " << testsPassed << " out of " << testsChecked << std::endl;
}
