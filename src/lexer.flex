%option noyywrap



D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include <stdio.h>
#include "parser.tab.hpp"
//YYSTYPE yylval;
%}

%%

"void"			{return(VOID); }
"int"			{return(INT); }
"enum"			{return(ENUM); }
"double"		{return(DOUBLE); }
"float"			{return(FLOAT); }
"char"			{return(CHAR); }
"unsigned"		{return(UNSIGNED); }
"typedef"		{return(TYPEDEF); }
"sizeof"		{return(SIZEOF); }
"struct"		{return(STRUCT); }

"do"			{return(DO); }
"if"			{return(IF); }
"else"			{return(ELSE); }
"return"		{return(RETURN); }
"while"			{return(WHILE); }
"for"			{return(FOR); }
"switch"		{return(SWITCH); }
"case"			{return(CASE); }
"break"			{return(BREAK); }
"continue"		{return(CONTINUE); }



{L}({L}|{D})*		    { yylval.string = new std::string(yytext); return(IDENTIFIER); }

0[xX]{H}+{IS}?		    {std::cerr<< "lexmatch 1\n"; yylval.string = new std::string(yytext); return(CONSTANT);  }
0{D}+{IS}?		        { std::cerr<< "lexmatch 2\n"; yylval.string = new std::string(yytext); return(CONSTANT);}
{D}+{IS}?		        { std::cerr<< "lexmatch 3\n"; yylval.string = new std::string(yytext); return(CONSTANT);}
L?'(\\.|[^\\'])+'	    { std::cerr<< "lexmatch 4\n"; yylval.string = new std::string(yytext); return(CONSTANT);}

{D}+{E}{FS}?		    {yylval.string = new std::string(yytext); return(CONSTANT); }
{D}*"."{D}+({E})?{FS}?	{yylval.string = new std::string(yytext); return(CONSTANT); }
{D}+"."{D}*({E})?{FS}?	{yylval.string = new std::string(yytext); return(CONSTANT); }

L?\"(\\.|[^\\"])*\"	    {yylval.string =  new std::string(yytext); return(STRING_LITERAL);  }

">>="			{return(RIGHT_ASSIGN); }
"<<="			{return(LEFT_ASSIGN); }
"+="			{return(ADD_ASSIGN); }
"-="			{return(SUB_ASSIGN); }
"*="			{return(MUL_ASSIGN); }
"/="			{return(DIV_ASSIGN); }
"%="			{return(MOD_ASSIGN); }
"&="			{return(AND_ASSIGN); }
"^="			{return(XOR_ASSIGN); }
"|="			{return(OR_ASSIGN); }
">>"			{return(RIGHT_OP); }
"<<"			{return(LEFT_OP); }
"++"			{return(INC_OP); }
"--"			{return(DEC_OP); }
"->"			{return(PTR_OP); }
"&&"			{return(AND_OP); }
"||"			{return(OR_OP); }
"<="			{return(LE_OP); }
">="			{return(GE_OP); }
"=="			{return(EQ_OP); }
"!="			{return(NE_OP); }
";"			    {return(';'); }
("{"|"<%")		{return('{'); }
("}"|"%>")		{return('}'); }
","			    {return(','); }
":"			    {return(':'); }
"="			    {return('='); }
"("			    {return('('); }
")"			    {return(')'); }
("["|"<:")		{return('['); }
("]"|":>")		{return(']'); }
"."			    {return('.'); }
"&"			    {return('&'); }
"!"			    {return('!'); }
"~"			    {return('~'); }
"-"			    {return('-'); }
"+"			    {return('+'); }
"*"			    {return('*'); }
"/"			    {return('/'); }
"%"			    {return('%'); }
"<"			    {return('<'); }
">"			    {return('>'); }
"^"			    {return('^'); }
"|"			    {return('|'); }
"?"			    {return('?'); }

[ \t\v\n\f]		{}
.			{ /* ignore bad characters */ }

%%

//Bison needs yyerror to work
void yyerror(char const* in){}


//int check_type()
//{
///*
//* pseudo code --- this is what it should check
//*
//*	if (yytext == type_name)
//*		return(TYPE_NAME);
//*
//*	return(IDENTIFIER);
//*/
//
///*
//*	it actually will only return IDENTIFIER
//*/
//
//	return(IDENTIFIER);
//}

