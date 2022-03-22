#include "../../include/ast.hpp"

int main() {
    Node *ast = parseAST();
    ast->generate_var_maps(ast);
    std::cout << "Parsed";
}
