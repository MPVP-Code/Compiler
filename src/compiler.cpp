#include<iostream>
#include "../include/ast.hpp"

int main(int argc, char *argv[]) {

    std::cerr << get_next_register("$22");
    std::cerr << get_next_register("$1");
    std::cerr << get_next_register("$a3");
    std::cerr << get_next_register("$t1");
    Node *ast = parseAST();

    //Important global parent is NULL!
    ast->generate_var_maps(NULL);


    std::cout << ast->compileToMIPS(NULL);

    return 0;
}
