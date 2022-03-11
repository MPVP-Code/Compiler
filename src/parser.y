%code requires{
#include "../include/ast.hpp"

#include <cassert>

extern Node* global_root; // A way of getting the AST out

int yylex(void);
void yyerror(const char *);

}


%union{
  const Node *node;
  int number;
  std::string *string;
  Type* type;
}

%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE VOLATILE VOID
%token STRUCT UNION ENUM

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR CONTINUE BREAK RETURN

%type <node> primary_expression postfix_expression unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression conditional_expression assignment_expression declaration declaration_specifiers init_declarator_list init_declarator logical_or_expression declarator initializer direct_declarator translation_unit
%type <node> external_declaration expression function_definition compound_statement
%type <number> CONSTANT
%type <string> IDENTIFIER
%type <type> type_specifier

%start translation_unit
%%

primary_expression
	: IDENTIFIER {}
	| CONSTANT {}
	| STRING_LITERAL {}
	| '(' expression ')' {}
	;

postfix_expression
	: primary_expression {}
	| postfix_expression '[' expression ']' {}
	| postfix_expression '(' ')' {}
	| postfix_expression '(' argument_expression_list ')' {}
	| postfix_expression '.' IDENTIFIER {}
	| postfix_expression PTR_OP IDENTIFIER {}
	| postfix_expression INC_OP {}
	| postfix_expression DEC_OP {}
	;

argument_expression_list
	: assignment_expression {}
	| argument_expression_list ',' assignment_expression {}
	;

unary_expression
	: postfix_expression {}
	| INC_OP unary_expression {}
	| DEC_OP unary_expression {}
	| unary_operator cast_expression {}
	| SIZEOF unary_expression {}
	| SIZEOF '(' type_name ')' {}
	;

unary_operator
	: '&' {}
	| '*' {}
	| '+' {}
	| '-' {}
	| '~' {}
	| '!' {}
	;

cast_expression
	: unary_expression {}
	| '(' type_name ')' cast_expression {}
	;

multiplicative_expression
	: cast_expression {}
	| multiplicative_expression '*' cast_expression {}
	| multiplicative_expression '/' cast_expression {}
	| multiplicative_expression '%' cast_expression {}
	;

additive_expression
	: multiplicative_expression {}
	| additive_expression '+' multiplicative_expression {}
	| additive_expression '-' multiplicative_expression {}
	;

shift_expression
	: additive_expression {}
	| shift_expression LEFT_OP additive_expression {}
	| shift_expression RIGHT_OP additive_expression {}
	;

relational_expression
	: shift_expression {}
	| relational_expression '<' shift_expression {}
	| relational_expression '>' shift_expression {}
	| relational_expression LE_OP shift_expression {}
	| relational_expression GE_OP shift_expression {}
	;

equality_expression
	: relational_expression {}
	| equality_expression EQ_OP relational_expression {}
	| equality_expression NE_OP relational_expression {}
	;

and_expression
	: equality_expression {}
	| and_expression '&' equality_expression {}
	;

exclusive_or_expression
	: and_expression {}
	| exclusive_or_expression '^' and_expression {}
	;

inclusive_or_expression
	: exclusive_or_expression {}
	| inclusive_or_expression '|' exclusive_or_expression {}
	;

logical_and_expression
	: inclusive_or_expression {}
	| logical_and_expression AND_OP inclusive_or_expression {}
	;

logical_or_expression
	: logical_and_expression {}
	| logical_or_expression OR_OP logical_and_expression {}
	;

conditional_expression
	: logical_or_expression {}
	| logical_or_expression '?' expression ':' conditional_expression {}
	;

assignment_expression
	: conditional_expression {}
	| unary_expression assignment_operator assignment_expression { }
	;

assignment_operator
	: '=' {}
	| MUL_ASSIGN {}
	| DIV_ASSIGN {}
	| MOD_ASSIGN {}
	| ADD_ASSIGN {}
	| SUB_ASSIGN {}
	| LEFT_ASSIGN {}
	| RIGHT_ASSIGN {}
	| AND_ASSIGN {}
	| XOR_ASSIGN {}
	| OR_ASSIGN {}
	;

expression
	: assignment_expression {}
	| expression ',' assignment_expression {}
	;

constant_expression
	: conditional_expression {}
	;

declaration
	: declaration_specifiers ';' {}
	| declaration_specifiers init_declarator_list ';' {}
	;

declaration_specifiers
	: storage_class_specifier {}
	| storage_class_specifier declaration_specifiers  {}
	| type_specifier {$$ = $1;}
	| type_specifier declaration_specifiers {}
	;

init_declarator_list
	: init_declarator {}
	| init_declarator_list ',' init_declarator {}
	;

init_declarator
	: declarator {}
	| declarator '=' initializer {}
	;

storage_class_specifier
	: TYPEDEF {}
	;

type_specifier
	: VOID {}
	//| CHAR {}
	| INT { $$ = new Type("int",4);
	std::cout << "found typespecifier";}
	//| FLOAT {}
	//| DOUBLE {}
	//| UNSIGNED {}
	//| struct_or_union_specifier {}
	//| enum_specifier {}
	//| TYPE_NAME {}
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}' {}
	| struct_or_union '{' struct_declaration_list '}' {}
	| struct_or_union IDENTIFIER {}
	;

struct_or_union
	: STRUCT {}
	| UNION {}
	;

struct_declaration_list
	: struct_declaration {}
	| struct_declaration_list struct_declaration {}
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';' {}
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list {}
	| type_specifier {}
	;

struct_declarator_list
	: struct_declarator {}
	| struct_declarator_list ',' struct_declarator {}
	;

struct_declarator
	: declarator {}
	| ':' constant_expression {}
	| declarator ':' constant_expression {}
	;

enum_specifier
	: ENUM '{' enumerator_list '}' {}
	| ENUM IDENTIFIER '{' enumerator_list '}' {}
	| ENUM IDENTIFIER {}
	;

enumerator_list
	: enumerator {}
	| enumerator_list ',' enumerator {}
	;

enumerator
	: IDENTIFIER {}
	| IDENTIFIER '=' constant_expression {}
	;

declarator
	: direct_declarator { std::cout << "declarator"; }
	//|  pointer direct_declarator {}
	;

direct_declarator
	: IDENTIFIER { std::cout << "found identifier";
		std::string *a = yylval.string;
		$$ = new Declarator(a);
	}
		| direct_declarator '(' ')' {std::cout << "dd()";}
		//| '(' declarator ')' {}
		//| direct_declarator '[' constant_expression ']' {}
		//| direct_declarator '[' ']' {}
		//| direct_declarator '(' parameter_type_list ')' {}
		//| direct_declarator '(' identifier_list ')' {}
		;

pointer
	: '*' {}
	| '*' pointer {}
	;

parameter_type_list
	: parameter_list {}
	;

parameter_list
	: parameter_declaration {}
	| parameter_list ',' parameter_declaration {}
	;

parameter_declaration
	: declaration_specifiers declarator {}
	| declaration_specifiers abstract_declarator {}
	| declaration_specifiers {}
	;

identifier_list
	: IDENTIFIER {}
	| identifier_list ',' IDENTIFIER {}
	;

type_name
	: specifier_qualifier_list {}
	| specifier_qualifier_list abstract_declarator {}
	;

abstract_declarator
	: pointer {}
	| direct_abstract_declarator {}
	| pointer direct_abstract_declarator {}
	;

direct_abstract_declarator
	: '(' abstract_declarator ')' {}
	| '[' ']' {}
	| '[' constant_expression ']' {}
	| direct_abstract_declarator '[' ']' {}
	| direct_abstract_declarator '[' constant_expression ']' {}
	| '(' ')' {}
	| '(' parameter_type_list ')' {}
	| direct_abstract_declarator '(' ')' {}
	| direct_abstract_declarator '(' parameter_type_list ')' {}
	;

initializer
	: assignment_expression {}
	| '{' initializer_list '}' {}
	| '{' initializer_list ',' '}' {}
	;

initializer_list
	: initializer {}
	| initializer_list ',' initializer {}
	;

statement
	: labeled_statement {}
	| compound_statement {}
	| expression_statement {}
	| selection_statement {}
	| iteration_statement {}
	| jump_statement {}
	;

labeled_statement
	: IDENTIFIER ':' statement {}
	| CASE constant_expression ':' statement {}
	| DEFAULT ':' statement {}
	;

compound_statement
	: '{' '}' { std::cout << "declaratorxxxx"; }
	| '{' statement_list '}' {std::cout << "declarator";}
	//| '{' declaration_list '}' {}
	//| '{' declaration_list statement_list '}' {}
	;

declaration_list
	: declaration {}
	| declaration_list declaration {}
	;

statement_list
	: statement {std::cout << "statement";}
	| statement_list statement {}
	;

expression_statement
	: ';' {std::cout << "exprstatement";}
	| expression ';' {}
	;

selection_statement
	: IF '(' expression ')' statement {}
	| IF '(' expression ')' statement ELSE statement {}
	| SWITCH '(' expression ')' statement {}
	;

iteration_statement
	: WHILE '(' expression ')' statement {}
	| DO statement WHILE '(' expression ')' ';' {}
	| FOR '(' expression_statement expression_statement ')' statement {}
	| FOR '(' expression_statement expression_statement expression ')' statement {}
	;

jump_statement
	: CONTINUE ';' {}
	| BREAK ';' {}
	| RETURN ';' {}
	| RETURN expression ';' {}
	;

translation_unit
	: external_declaration { //global_root = new Global();
				//global_root->push_branch($1);
				std::cout << "Found function";
	 			}
	// | translation_unit external_declaration {$2->push_branch($1);	std::cout << "Found another";	}
	;

external_declaration
	: function_definition { std::cout << "found funcdef";
	$$ = $1;}
	//| declaration {$$ = $1;}
	;

function_definition
	: declaration_specifiers declarator compound_statement { std::cout<<"found func";
	//$$ = new Function($2,$3);
	}
	//| declaration_specifiers declarator declaration_list compound_statement {}
	//| declarator declaration_list compound_statement {}
	//| declarator compound_statement {}
	;

%%
#include <stdio.h>

extern char yytext[];

Node* global_root;

const Node *parseAST()
{
	global_root=0;
  	yyparse();
  	return global_root;
}


void yyerror(char *s){
	fflush(stdout);
	printf("\n%*s\n%*s\n", "^", s);
}
