
ANSI C grammar, Lex specification
Jutta Degener, 1995 ; Reduced and adapted , Michal Palic, Vaclav Pavlicek 2022


D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{
#include <stdio.h>
#include "parser.tab.hpp"

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

"if"			{return(IF); }
"else"			{return(ELSE); }
"return"		{return(RETURN); }
"while"			{return(WHILE); }
"for"			{return(FOR); }
"switch"		{return(SWITCH); }
"case"			{return(CASE); }
"break"			{return(BREAK); }
"continue"		{return(CONTINUE); }



{L}({L}|{D})*		    {return(check_type()); }

0[xX]{H}+{IS}?		    {return(CONSTANT); }
0{D}+{IS}?		        {return(CONSTANT); }
{D}+{IS}?		        {return(CONSTANT); }
L?'(\\.|[^\\'])+'	    {return(CONSTANT); }

{D}+{E}{FS}?		    {return(CONSTANT); }
{D}*"."{D}+({E})?{FS}?	{return(CONSTANT); }
{D}+"."{D}*({E})?{FS}?	{return(CONSTANT); }

L?\"(\\.|[^\\"])*\"	    {return(STRING_LITERAL); }

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

yywrap()
{
	return(1);
}


comment()
{
	char c, c1;

loop:
	while ((c = input()) != '*' && c != 0)
		putchar(c);

	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}

	if (c != 0)
		putchar(c1);
}

int check_type()
{
/*
* pseudo code --- this is what it should check
*
*	if (yytext == type_name)
*		return(TYPE_NAME);
*
*	return(IDENTIFIER);
*/

/*
*	it actually will only return IDENTIFIER
*/

	return(IDENTIFIER);
}

