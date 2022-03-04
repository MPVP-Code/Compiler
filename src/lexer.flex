%option noyywrap

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */
// for parser
#include "parser.tab.hpp"
// for lexer
// #include "lexer.hpp"

// This is to work around an irritating bug in Flex
// https://stackoverflow.com/questions/46213840/get-rid-of-warning-implicit-declaration-of-function-fileno-in-flex
extern "C" int fileno(FILE *stream);

%}


%%

[a-zA-Z]+       { fprintf(stderr, "variable\n"); yylval.string=new std::string(yytext); /* TODO: check deallocation of this */ return VARIABLE; }

[\-]?[0-9]+     { fprintf(stderr, "number %f\n", std::stod(yytext, 0)); yylval.number=std::stod(yytext, 0); return NUMBER; }

=               { fprintf(stderr, "equals\n"); return EQUALS_SIGN; }

\n              { ; }

.   { fprintf(stderr, "All other chars, \n"); }

%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}
