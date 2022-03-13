%code requires{
#include "../include/ast.hpp"

#include <cassert>

extern Global* global_root; // A way of getting the AST out

int yylex(void);
void yyerror(const char *);

}


%union{
  Node *node;
  int number;
  std::string *string;
  std::vector<Node*>* statements;
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

%type <node>  multiplicative_expression additive_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression conditional_expression assignment_expression logical_or_expression initializer translation_unit
%type <node>  expression function_definition
%type <node> statement expression_statement
%type <node> primary_expression postfix_expression unary_expression
%type <string> CONSTANT
%type <string> IDENTIFIER
%type <string> type_specifier declaration_specifiers  direct_declarator declarator
%type <statements> compound_statement statement_list external_declaration declaration init_declarator_list init_declarator


%start translation_unit
%%

primary_expression
	: IDENTIFIER { $$ = new Identifier(*$1); std::cout << "found identifier\n" << *$1 << std::endl;}
	| CONSTANT { $$ = new Constant(std::stoi(*$1)); std::cout<<"Found const\n" << *$1 << std::endl;}
//	| STRING_LITERAL {}
//	| '(' expression ')' {}
	;

postfix_expression
	: primary_expression {$$ = $1; }
//	| postfix_expression '[' expression ']' {}
//	| postfix_expression '(' ')' {}
//	| postfix_expression '(' argument_expression_list ')' {}
//	| postfix_expression '.' IDENTIFIER {}
//	| postfix_expression PTR_OP IDENTIFIER {}
//	| postfix_expression INC_OP {}
//	| postfix_expression DEC_OP {}
	;

argument_expression_list
	: assignment_expression {}
	| argument_expression_list ',' assignment_expression {}
	;

unary_expression
	: postfix_expression {$$ = $1; std::cout<< "unary postfix expression\n";}
//	| INC_OP unary_expression {}
//	| DEC_OP unary_expression {}
//	| unary_operator cast_expression {}
//	| SIZEOF unary_expression {}
//	| SIZEOF '(' type_name ')' {}
	;

unary_operator
	: '&' {}
	| '*' {}
	| '+' {}
	| '-' {}
	| '~' {}
	| '!' {}
	;


multiplicative_expression
	: unary_expression {
		if($1->type == "Identifier"){
		$$ = new Variable ("None", ((Identifier*)$1)->identifier, false); }
		}
//	| multiplicative_expression '*' unary_expression {}
//	| multiplicative_expression '/' unary_expression {}
//	| multiplicative_expression '%' unary_expression {}
	;

additive_expression
	: multiplicative_expression {$$ = $1;}
	| additive_expression '+' multiplicative_expression {$$ = new Addition ($1, $3); }
	| additive_expression '-' multiplicative_expression {$$ = new Subtraction ($1, $3);}
	;

shift_expression
	: additive_expression {$$ = $1;}
//	| shift_expression LEFT_OP additive_expression {}
//	| shift_expression RIGHT_OP additive_expression {}
	;

relational_expression
	: shift_expression {$$ =$1;}
//	| relational_expression '<' shift_expression {}
//	| relational_expression '>' shift_expression {}
//	| relational_expression LE_OP shift_expression {}
//	| relational_expression GE_OP shift_expression {}
	;

equality_expression
	: relational_expression {$$ = $1;}
//	| equality_expression EQ_OP relational_expression {}
//	| equality_expression NE_OP relational_expression {}
	;

and_expression
	: equality_expression {$$ = $1;}
	//| and_expression '&' equality_expression {}
	;

exclusive_or_expression
	: and_expression {$$ = $1;}
	//| exclusive_or_expression '^' and_expression {}
	;

inclusive_or_expression
	: exclusive_or_expression {$$ = $1;}
	//| inclusive_or_expression '|' exclusive_or_expression {}
	;

logical_and_expression
	: inclusive_or_expression {$$ = $1;}
	//| logical_and_expression AND_OP inclusive_or_expression {}
	;

logical_or_expression
	: logical_and_expression {$$ = $1;}
	//| logical_or_expression OR_OP logical_and_expression {}
	;

conditional_expression
	: logical_or_expression {$$ = $1; std::cout<< "found conditional expression\n"; }
	//| logical_or_expression '?' expression ':' conditional_expression {}
	;

assignment_expression
	: unary_expression assignment_operator assignment_expression {
		auto temp = new Variable("int", ((Identifier*)$1)->identifier, false);
		$$ = new Assign(temp, $3);
	 }
	| conditional_expression {$$ = $1; }
	;

assignment_operator
	: '=' { std::cout<<"Found =\n";}
//	| MUL_ASSIGN {}
//	| DIV_ASSIGN {}
//	| MOD_ASSIGN {}
//	| ADD_ASSIGN {}
//	| SUB_ASSIGN {}
//	| LEFT_ASSIGN {}
//	| RIGHT_ASSIGN {}
//	| AND_ASSIGN {}
//	| XOR_ASSIGN {}
//	| OR_ASSIGN {}
	;

expression
	: assignment_expression {$$ = $1;}
	//| expression ',' assignment_expression {}
	;

constant_expression
	: conditional_expression {}
	;

declaration
	: declaration_specifiers init_declarator_list ';' { // Set type of all assignments
		for (auto statement : *$2){
			if(statement -> type == "Variable"){
				auto temp = (Variable*) statement;
				if (temp->declaration){
					temp->variable_type = *$1;
				}
			}
		}
		$$ = $2;

	}
//	| declaration_specifiers ';' {}
	;

declaration_specifiers
	: type_specifier {$$ = $1; std::cout<< "found type specifier\n"; }
	| type_specifier declaration_specifiers {}
//	| storage_class_specifier declaration_specifiers  {}
//	| storage_class_specifier {}
	;

init_declarator_list
	: init_declarator {$$ = $1;}
	| init_declarator_list ',' init_declarator {$1->insert($1->end(), $3->begin(), $3->end());
						delete $3;
						}
	;

init_declarator
	: declarator {$$ = new std::vector<Node*>;
			auto temp = new Variable("None", *$1, true);
			$$-> push_back(temp);
	}
	| declarator '=' initializer {
			$$ = new std::vector<Node*>;
			auto temp = new Variable("None", *$1, true);
			$$-> push_back(temp);
			auto temp2 = new Assign(temp, $3);
			$$-> push_back(temp2);

	}
	;

storage_class_specifier
	: TYPEDEF {}
	;

type_specifier
	: INT { $$ = new std::string("int");}
//	| CHAR {}
//	| VOID {}
//	| FLOAT {}
//	| DOUBLE {}
//	| UNSIGNED {}
//	| struct_or_union_specifier {}
//	| enum_specifier {}
//	| TYPE_NAME {}
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
	: direct_declarator { $$ = $1; std::cout << "found directcdeclarator\n"; }
	//|  pointer direct_declarator {}
	;

direct_declarator
	: IDENTIFIER { $$ = $1;	}
	| direct_declarator '(' ')' {$$ = $1;}
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
//	| '{' initializer_list '}' {}  //Array stuff
//	| '{' initializer_list ',' '}' {}
	;

initializer_list
	: initializer {}
	| initializer_list ',' initializer {}
	;

statement
	: expression_statement {$$ = $1; }
	//| compound_statement {}
//	| labeled_statement {}
//	| selection_statement {}
//	| iteration_statement {}
//	| jump_statement {}
	;

//labeled_statement
//	: IDENTIFIER ':' statement {}
//	| CASE constant_expression ':' statement {}
//	| DEFAULT ':' statement {}
//	;

compound_statement
	: '{' '}' { $$ = new std::vector<Node*>(); std::cout << "found empty statement\n";	}
	| '{' statement_list '}' {$$ = $2; std::cout << "found statement list\n"; }
	//| '{' declaration_list '}' {}
	//| '{' declaration_list statement_list '}' {}
	;

declaration_list
	: declaration {}
	| declaration_list declaration {}
	;

statement_list
	: statement {
	std::cout << "found statement\n";
		$$ = new std::vector<Node*>();
				if ($1 != 0){
					$$->push_back($1);
				}
			}
	| statement_list statement {
		$1->push_back($2);
		$$ = $1;
	}

	;

expression_statement
	: ';' {$$ = 0;}
	| expression ';' {$$ = $1;}
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
	: external_declaration { global_root = new Global();
				global_root->branches.insert(global_root->branches.end(), $1->begin(), $1->end());
				std::cout << "Found function\n";
	 			}
	| translation_unit external_declaration {
				global_root->branches.insert(global_root->branches.end(), $2->begin(), $2->end());
				std::cout << "Found another";
				}
	;

external_declaration
	: function_definition { $$ = new std::vector<Node*>();
	$$->push_back($1);
	std::cout << "found funcdef\n";}
	| declaration {
	$$ = $1;}
	;

function_definition
	: declaration_specifiers declarator compound_statement {
	std::cout<<"found function";
	$$ = new FunctionDeclaration(*$1,*$2,*$3);
	}
	//| declaration_specifiers declarator declaration_list compound_statement {}
	//| declarator declaration_list compound_statement {}
	//| declarator compound_statement {}
	;

%%
#include <stdio.h>

extern char yytext[];

Global* global_root;

const Node *parseAST()
{
	global_root=0;
  	yyparse();
  	(*global_root).generate_var_maps(global_root);
  	return global_root;
}


void yyerror(char *s){
	fflush(stdout);
	printf("\n%*s\n%*s\n", "^", s);
}
