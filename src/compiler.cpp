#include<iostream>
#include <iomanip>
#include "../include/ast.hpp"
#include "../include/register_allocator.hpp"
#include "../build/parser.tab.hpp"

int main(int argc, char *argv[]) {
    Node *ast = parseAST();
    ast->generate_var_maps(ast);

    RegisterAllocator::initCurrentRegister();
    RegisterAllocator::reinitRegistersMappingMap();

    std::cout << ast->compileToMIPS();

    return 0;
}
