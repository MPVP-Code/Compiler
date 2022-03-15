#include "../include/ast/ast_syntax.h"
//#include "../include/ast/ast_scope.h"

int main() {
    Identifier* identifier = new Identifier("hello");
    std::cout << "identifier name: " << identifier->identifier << std::endl;
    //Identifiera* scope = new Identifiera("hello");
    //scope->generate_var_maps(nullptr);
}