#include "../include/ast/ast_arithmetic.h"
#include "../include/ast/ast_assignment.h"
#include "../include/ast/ast_func.h"
#include "../include/ast/ast_jump_statement.h"
#include "../include/ast/ast_node.h"
#include "../include/ast/ast_scope.h"
#include "../include/ast/ast_syntax.h"
#include "../include/ast/ast_variable.h"

int main() {
    Identifier* identifier = new Identifier("hello");
    std::cout << "identifier name: " << identifier->identifier << std::endl;
    Scope* scope = new Scope();
    scope->generate_var_maps(nullptr);
    std::vector<Node*> statements;
    FunctionDeclaration* funcDef = new FunctionDeclaration("void", "a", statements);
    Constant *constant1 = new Constant(10);
    Constant *constant2 = new Constant(10);
    Addition *addition = new Addition(constant1, constant2);
    Return *returnStatement = new Return(addition);
    Variable *varA = new Variable("int", "a", true);
    Constant *constant3 = new Constant(20);
    Assign *assignment = new Assign(varA, constant3);
    std::cout << assignment->compileToMIPS() << std::endl;
}