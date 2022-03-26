#include<iostream>
#include "../include/ast.hpp"

int main(int argc, char *argv[]) {
    Node *ast = parseAST();

    //Important global parent is NULL!
    ast->generate_var_maps(NULL);

//    RegisterAllocator::initCurrentRegister();
//    RegisterAllocator::reinitRegistersMappingMap();

    std::cout << ast->compileToMIPS(NULL);

    return 0;
}
