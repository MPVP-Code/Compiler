%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const Expression *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Expression *expr;
  double number;
  std::string *string;
}

%token NUMBER
%token VARIABLE EQUALS_SIGN

%type <expr> EXPR
%type <number> NUMBER
%type <string> VARIABLE EQUALS_SIGN

%start ROOT

%%

ROOT : EXPR { g_root = $1; }

EXPR : VARIABLE EQUALS_SIGN NUMBER { $$ = new AssignmentOperator(new Variable(*$1), new Number($3)); }

%%

const Expression *g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}