#include <limits.h>
#include <vector>
#include "gtest/gtest.h"
#include "../include/ast.hpp"

namespace {

    /*
     * Code that should be generated
     * void a() {
     * int b = 10;
     * }
     * */
    TEST(FunctionTest, VoidFunctionCompilation) {
        Variable* variable = new Variable("int", "b");
        Constant* constant = new Constant(10);
        Assign* assign = new Assign(variable, constant);
        std::vector<Node*> statements;
        statements.push_back(assign);
        Function *function = new Function("void", "a", statements);
        //Global::initCurrentRegister();

        std::string expectedCode = "a():\nli $2, 0x10";

        EXPECT_EQ(expectedCode, function->compileToMIPS());
    }
}