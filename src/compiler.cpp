#include<iostream>
#include "../include/ast.hpp"

int main(int argc, char *argv[]) {
    Node *ast = parseAST();
    ast->generate_var_maps(ast);

    RegisterAllocator::initCurrentRegister();
    RegisterAllocator::reinitRegistersMappingMap();

    std::cout << ast->compileToMIPS(NULL);

    return 0;
}
