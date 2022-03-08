#include "ast.hpp"

int main() {
    const Expression *ast = parseAST();

    std::cout << ast->to_string() << std::endl;

    return 0;
}
