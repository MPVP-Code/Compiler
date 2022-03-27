#include<iostream>
#include "../include/ast.hpp"

int main(int argc, char *argv[]) {
    Node *ast = parseAST();

    //Important global parent is NULL!
    ast->generate_var_maps(NULL);

    std::cout << ".section .mdebug.abi32\n.previous\n.nan legacy\n.module fp=32\n.module nooddspreg" << std::endl;

    std::cout << ast->compileToMIPS(NULL);

    return 0;
}
