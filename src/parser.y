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
  char character;
}

%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF NEW_TYPE_NAME CONSTANT_FLOAT
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE VOLATILE VOID
%token STRUCT UNION ENUM

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR CONTINUE BREAK RETURN
%type <node>  multiplicative_expression additive_expression shift_expression relational_expression equality_expression
%type <node> and_expression exclusive_or_expression inclusive_or_expression logical_and_expression conditional_expression
%type <node> assignment_expression logical_or_expression initializer translation_unit
%type <node>  expression function_definition constant_expression
%type <node>  labeled_statement expression_statement selection_statement parameter_declaration
%type <node> primary_expression postfix_expression unary_expression jump_statement iteration_statement declarator direct_declarator
%type <string> CONSTANT CONSTANT_FLOAT
%type <string> IDENTIFIER
%type <string> type_specifier declaration_specifiers specifier_qualifier_list type_name pointer NEW_TYPE_NAME storage_class_specifier
%type <statements> compound_statement statement_list external_declaration declaration init_declarator_list init_declarator
%type <statements> declaration_list statement parameter_list parameter_type_list argument_expression_list
%type <character> unary_operator assignment_operator

%start translation_unit
%%

primary_expression
	: IDENTIFIER { //$$ = new Identifier(*$1); std::cerr << "found identifier\n" << *$1 << std::endl;
			$$ = new Variable ("", *$1, false);
			}
	| CONSTANT { $$ = new Constant(std::stoi(*$1)); $$->data_type = "int"; std::cerr<<"Found int const\n" << *$1 << std::endl;}
	| CONSTANT_FLOAT {  $$ = new ConstantFloat(std::stof(*$1)); $$->data_type = "float"; std::cerr<<"Found float const\n" << *$1 << std::endl; }
//	| STRING_LITERAL {}
	| '(' expression ')' {$$ = $2;}
	;

postfix_expression
	: primary_expression {$$ = $1; }

	| postfix_expression '(' ')' {
				auto id = (Variable*) $1;
				auto empty  = new std::vector<Node*>();
				$$ = new FunctionCall(id->name, empty);}
	| postfix_expression '(' argument_expression_list ')' {
				auto id = (Variable*) $1;
				$$ = new FunctionCall(id->name, $3);
	}
//	| postfix_expression '[' expression ']' {}
//	| postfix_expression '.' IDENTIFIER {}
//	| postfix_expression PTR_OP IDENTIFIER {}
	| postfix_expression INC_OP { $$ = new PostIncOp ($1); }
	| postfix_expression DEC_OP { $$ = new PostDecOp ($1); }
	;

argument_expression_list
	: assignment_expression {
		$$ = new std::vector<Node*>();
		$$->push_back($1);
	}
	| argument_expression_list ',' assignment_expression {
		$1->push_back($3);
		$$ = $1;
	}
	;

unary_expression
	: postfix_expression { $$ = $1;	}
	| INC_OP unary_expression {$$ = new PreIncOp ($2);}
	| DEC_OP unary_expression {$$ = new PreDecOp ($2);}
	| unary_operator unary_expression {
	if ($1 == '~'){
		$$ = new BitNot ($2);
	} else if ($1 == '!'){
		$$ = new LogicNot($2);
	} else if ($1 == '-'){
		$$ = new UnaryMinus($2);
	}else if ($1 == '+'){
		$$ = $2;
	}else if ($1 == '&'){
		$$ = new AddressOf($2);
	}else if ($1 == '*'){
		$$ = new Dereference($2);
	}

	}
	| SIZEOF unary_expression {$$ = new SizeOf($2);}
	| SIZEOF '(' type_name ')' {
		auto con = new Constant(0);
		con->data_type = *$3;
		$$ = new SizeOf(con);}
	;

unary_operator
	: '&' {$$ = '&';}
	| '*' {$$ = '*'; std::cerr<< "Found unary dereference"; }
	| '+' {$$ = '+';}
	| '-' {$$ = '-';}
	| '~' {$$ = '~';}
	| '!' {$$ = '!';}
	;


multiplicative_expression
	: unary_expression {$$ = $1;}
	| multiplicative_expression '*' unary_expression {$$ = new Multiplication ($1, $3);}
	| multiplicative_expression '/' unary_expression {$$ = new Division ($1, $3);}
	| multiplicative_expression '%' unary_expression {$$ = new Modulo ($1, $3);}
	;

additive_expression
	: multiplicative_expression {$$ = $1;}
	| additive_expression '+' multiplicative_expression {$$ = new Addition ($1, $3); }
	| additive_expression '-' multiplicative_expression {$$ = new Subtraction ($1, $3);}
	;

shift_expression
	: additive_expression {$$ = $1;}
	| shift_expression LEFT_OP additive_expression {$$ = new BitASL($1, $3);}
	| shift_expression RIGHT_OP additive_expression {$$ = new BitASR($1, $3);}
	;

relational_expression
	: shift_expression {$$ =$1;}
	| relational_expression '<' shift_expression {$$ = new LogicLT($1,$3);}
	| relational_expression '>' shift_expression {$$ = new LogicGT($1,$3);}
	| relational_expression LE_OP shift_expression {$$ = new LogicLE($1,$3);}
	| relational_expression GE_OP shift_expression {$$ = new LogicGE($1,$3);}
	;

equality_expression
	: relational_expression {$$ = $1;}
	| equality_expression EQ_OP relational_expression {$$ = new LogicEQ($1,$3);}
	| equality_expression NE_OP relational_expression {$$ = new LogicNE($1,$3);}
	;

and_expression
	: equality_expression {$$ = $1;}
	| and_expression '&' equality_expression {$$ = new BitAnd($1, $3);}
	;

exclusive_or_expression
	: and_expression {$$ = $1;}
	| exclusive_or_expression '^' and_expression {$$ = new BitXor($1, $3);}
	;

inclusive_or_expression
	: exclusive_or_expression {$$ = $1;}
	| inclusive_or_expression '|' exclusive_or_expression {$$ = new BitOr($1, $3);}
	;

logical_and_expression
	: inclusive_or_expression {$$ = $1;}
	| logical_and_expression AND_OP inclusive_or_expression {$$ = new LogicAnd($1, $3); }
	;

logical_or_expression
	: logical_and_expression {$$ = $1;}
	| logical_or_expression OR_OP logical_and_expression {$$ = new LogicOr($1,$3);}
	;

conditional_expression
	: logical_or_expression {$$ = $1; }
	//| logical_or_expression '?' expression ':' conditional_expression {}
	;

assignment_expression
	: unary_expression assignment_operator assignment_expression {
		//Support for left dereference
		Node* temp;

		std::cerr<<"assignmentexpression" <<" assop = "<< $2 << "Unexp type" << $1->type << std::endl;

		temp = $1;

		if ($2 == '='){
			$$ = new Assign(temp, $3);
		}else if($2 == '*'){
			Node* op = new Multiplication(temp, $3);
			$$ = new Assign(temp, op);
		}
		else if($2 == '/'){
			Node* op = new Division(temp, $3);
			$$ = new Assign(temp, op);
		}
		else if($2 == '%'){
			Node* op = new Modulo(temp, $3);
			$$ = new Assign(temp, op);
		}else if($2 == '+'){
			Node* op = new Addition(temp, $3);
			$$ = new Assign(temp, op);
		}else if($2 == '-'){
			Node* op = new Subtraction(temp, $3);
			$$ = new Assign(temp, op);
		}else if($2 == '<'){
			Node* op = new BitASL(temp, $3);
			$$ = new Assign(temp, op);
		}else if($2 == '>'){
			Node* op = new BitASR(temp, $3);
			$$ = new Assign(temp, op);
		}else if($2 == '&'){
			Node* op = new BitAnd(temp, $3);
			$$ = new Assign(temp, op);
		}else if($2 == '^'){
			Node* op = new BitXor(temp, $3);
			$$ = new Assign(temp, op);
		}
		else if($2 == '|'){
			Node* op = new BitOr(temp, $3);
			$$ = new Assign(temp, op);
		}
	 }
	| conditional_expression {$$ = $1; }
	;

assignment_operator
	: '=' { $$ = '='; }
	| MUL_ASSIGN {$$ = '*';}
	| DIV_ASSIGN {$$ = '/';}
	| MOD_ASSIGN {$$ = '%';}
	| ADD_ASSIGN {$$ = '+';}
	| SUB_ASSIGN {$$ = '-';}
	| LEFT_ASSIGN {$$ = '<';}
	| RIGHT_ASSIGN {$$ = '<';}
	| AND_ASSIGN {$$ = '&';}
	| XOR_ASSIGN {$$ = '^';}
	| OR_ASSIGN {$$ = '|';}
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
					if (temp->data_type != ""){
						std::cerr<<"Merging type:" + *$1 << ": " << temp->data_type;
						temp->data_type = *$1 + temp->data_type;
					}else {
					temp->data_type = *$1;
					}
				}
			} else if (statement->subtype == "FunctionDeclaration"){
				//Forward function declarations parsed through here
				auto temp = (FunctionDeclaration*) statement;
				temp->return_type = $1;
				std::cerr << "Found fwd declaration\n";


			}
		}
		$$ = $2;

	}
	| declaration_specifiers ';' {}
	;

declaration_specifiers
	: type_specifier {$$ = $1;}
	| type_specifier declaration_specifiers {$$ = $1;}
	//| storage_class_specifier declaration_specifiers  {$$ = new TypeDef(*$1, *$2);}
	//| storage_class_specifier {$$ = $1;}
	;

init_declarator_list
	: init_declarator {$$ = $1;
		std::cerr << "found init_declarator\n" << ((*$1)[0])->type;}
	| init_declarator_list ',' init_declarator {
		$1->insert($1->end(), $3->begin(), $3->end());
		$$ = $1;
		}
	;

init_declarator
	: declarator {$$ = new std::vector<Node*>;
			std::cerr<< $1->type;
			std::cerr<< $1->subtype;


			if ($1->subtype == "FunctionDeclaration"){
				auto func = (FunctionDeclaration*)$1;
				//If a function declaration got here it is a fwd declaration
				func->forward_declaration = true;
				$$->push_back(func);
			} else {
				auto var  = (Variable*) $1;
				var->declaration = true;
				$$-> push_back(var);
			}
	}
	| declarator '=' initializer {
			$$ = new std::vector<Node*>;
			auto var = (Variable*)$1;
			var->declaration = true;
			$$-> push_back(var);
			auto temp2 = new Assign($1, $3);
			$$-> push_back(temp2);

	}
	;

storage_class_specifier
	: TYPEDEF { $$ = new std::string("typedef");}
	;

type_specifier
	: INT { $$ = new std::string("int");}
	| CHAR {$$ = new std::string("char");}
	| VOID {$$ = new std::string("void");}
	| FLOAT {$$ = new std::string("float");}
	| DOUBLE {$$ = new std::string("double");}
	| UNSIGNED {$$ = new std::string("unsigned");}
//	| struct_specifier {}
//	| enum_specifier {}
//	| TYPE_NAME {}
	;

struct_specifier
	: STRUCT IDENTIFIER '{' struct_declaration_list '}' {}
	| STRUCT '{' struct_declaration_list '}' {}
	| STRUCT IDENTIFIER {}
	;

struct_declaration_list
	: struct_declaration {}
	| struct_declaration_list struct_declaration {}
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';' {}
	;

specifier_qualifier_list
	: type_specifier {$$ = $1;}
	//| type_specifier specifier_qualifier_list {}
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
	: direct_declarator { $$ = $1; }
	|  pointer direct_declarator {
		auto var= (Variable*) $2;
		std::cerr<<"Pointer value" << $1;
		var->data_type = *$1;
		$$ = var;

		}
	;

direct_declarator
	: IDENTIFIER { $$ = new Variable("", *$1, false);	}
	| direct_declarator '(' ')' {
		auto var = (Variable*)$1;
		auto func =  new FunctionDeclaration();
		func->arguments = new std::vector<Variable*>();
		func->name = var->name;
		$$ = func;
	}
	| direct_declarator '(' parameter_type_list ')' {
			auto var = (Variable*)$1;
        		auto func =  new FunctionDeclaration();
        		func->name = var->name;

        		//Copy with cast to var
        		func->arguments = new std::vector<Variable*>();
        		for(auto arg : *$3){
        			auto var = (Variable*) arg;
        			func->arguments->push_back(var);
        			func->var_map[var->name] = var;
        		}
        		$$ = func;
	}
	| '(' declarator ')' {$$ = $2;}
	//| direct_declarator '[' constant_expression ']' {}
	//| direct_declarator '[' ']' {}

	//| direct_declarator '(' identifier_list ')' {}
	;

pointer
	: '*' {$$ = new std::string("*");}
	| '*' pointer {
		auto str = *$2 + "*";
		$$ = new std::string(str);
		std::cerr<<str;
		}
	;

parameter_type_list
	: parameter_list {$$ = $1;}
	;

parameter_list
	: parameter_declaration {$$ = new std::vector<Node*>();
				$$->push_back($1);}
	| parameter_list ',' parameter_declaration {$1->push_back($3);\
	$$ =$1; }
	;

parameter_declaration
	: declaration_specifiers declarator {
		auto var = (Variable*) $2;
		var->declaration = true;
		var->data_type = *$1 + var->data_type;
		$$ = var;
	 }
	//| declaration_specifiers abstract_declarator {}
	//| declaration_specifiers {}
	;

identifier_list
	: IDENTIFIER {}
	| identifier_list ',' IDENTIFIER {}
	;

type_name
	: specifier_qualifier_list {$$ = $1;}
//	| specifier_qualifier_list abstract_declarator {}
	;

//abstract_declarator
//	: pointer {}
//	| direct_abstract_declarator {}
//	| pointer direct_abstract_declarator {}
//	;

//direct_abstract_declarator
//	: '(' abstract_declarator ')' {}
//	| '[' ']' {}
//	| '[' constant_expression ']' {}
//	| direct_abstract_declarator '[' ']' {}
//	| direct_abstract_declarator '[' constant_expression ']' {}
//	| '(' ')' {}
//	| '(' parameter_type_list ')' {}
//	| direct_abstract_declarator '(' ')' {}
//	| direct_abstract_declarator '(' parameter_type_list ')' {}
//	;

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
	: expression_statement { $$ = new std::vector<Node*>();
				$$->push_back($1); }
	| compound_statement {	 $$ = new std::vector<Node*>();
				auto temp = new CompoundStatement(*$1);
				$$->push_back(temp);
				}

	| labeled_statement {$$ = new std::vector<Node*>();
                            	$$->push_back($1);}
	| selection_statement {$$ = new std::vector<Node*>();
				$$->push_back($1);}
	| iteration_statement {	$$ = new std::vector<Node*>();
				$$->push_back($1);
                               }

	| jump_statement {	$$ = new std::vector<Node*>();
				$$->push_back($1);}
	;

labeled_statement
	: CASE constant_expression ':' statement {
				if ($4->size() != 0 && $4->at(0)->type == "Scope" && $4->at(0)->subtype == "CompoundStatement" ){
					$$ = new Case($2, ((CompoundStatement*)($4->at(0)))->statements);
				}else{
					$$ = new Case($2, *$4);}
				 }
	| IDENTIFIER ':' statement {
				if ($3->size() != 0 && $3->at(0)->type == "Scope" && $3->at(0)->subtype == "CompoundStatement" ){
					$$ = new DefaultCase( ((CompoundStatement*)($3->at(0)))->statements);
				}else{
					$$ = new DefaultCase(*$3); }


	$$ = new DefaultCase(*$3); }
	//| DEFAULT ':' statement { $$ = new DefaultCase(*$3); }
	;

compound_statement
	: '{' '}' { $$ = new std::vector<Node*>();}
	| '{' statement_list '}' {$$ = $2; }
	| '{' declaration_list '}' {$$ = $2; }
	| '{' declaration_list statement_list '}' { $2->insert($2->end(), $3->begin(), $3->end());
							$$ = $2;
	}
	;

declaration_list
	: declaration {$$ = $1;}
	| declaration_list declaration {$1->insert($1->end(), $2->begin(), $2->end());
					$$ = $1;}
	;

statement_list
	: statement {$$ = $1;}
	| statement_list statement {
		$1->insert($1->end(),$2->begin(), $2->end());
		$$ = $1;
	}

	;

expression_statement
	: ';' {$$ = NULL;}
	| expression ';' {$$ = $1;}
	;

selection_statement
	: IF '(' expression ')' statement {
				if ($5->size() != 0 && $5->at(0)->type == "Scope" && $5->at(0)->subtype == "CompoundStatement" ){
					$$ = new If($3, &(((CompoundStatement*)($5->at(0)))->statements), NULL);
				}else{
					$$ = new If($3, $5, NULL);
				}
	 }
	| IF '(' expression ')' statement ELSE statement {
				std::vector<Node*>* stat1;
				if ($5->size() != 0 && $5->at(0)->type == "Scope" && $5->at(0)->subtype == "CompoundStatement" ){
					stat1 = &(((CompoundStatement*)($5->at(0)))->statements);
				}else{
					stat1 = $5;
				}

				std::vector<Node*>* stat2;
				if ($7->size() != 0 && $7->at(0)->type == "Scope" && $7->at(0)->subtype == "CompoundStatement" ){
					stat2 = &(((CompoundStatement*)($7->at(0)))->statements);
				}else{
					stat2 = $7;
				}

				$$ = new If($3, stat1, stat2); /*TODO: could be problematic, because passing pointers*/
				}
	| SWITCH '(' expression ')' statement {
				if ($5->size() != 0 && $5->at(0)->type == "Scope" && $5->at(0)->subtype == "CompoundStatement" ){
					$$ = new Switch($3, (((CompoundStatement*)($5->at(0)))->statements));
				}else{
					$$ = new Switch($3, *$5);
				}
				}
	;

iteration_statement
	: WHILE '(' expression ')' statement {
				if ($5->size() != 0 && $5->at(0)->type == "Scope" && $5->at(0)->subtype == "CompoundStatement" ){
					$$ = new While($3, (((CompoundStatement*)($5->at(0)))->statements));
				}else{
					$$ = new While($3, *$5);
				}
				}
	| DO statement WHILE '(' expression ')' ';' {
				if ($2->size() != 0 && $2->at(0)->type == "Scope" && $2->at(0)->subtype == "CompoundStatement" ){
					$$ = new DoWhile($5, (((CompoundStatement*)($2->at(0)))->statements));
				}else{
					$$ = new DoWhile($5, *$2);
				}
				}
	| FOR '(' expression_statement expression_statement ')' statement {
				if ($6->size() != 0 && $6->at(0)->type == "Scope" && $6->at(0)->subtype == "CompoundStatement" ){
					$$ = new For($3, $4, NULL, (((CompoundStatement*)($6->at(0)))->statements));
				}else{
					$$ = new For($3, $4, NULL, *$6);
				}
				}
	| FOR '(' expression_statement expression_statement expression ')' statement {
				if ($7->size() != 0 && $7->at(0)->type == "Scope" && $7->at(0)->subtype == "CompoundStatement" ){
					$$ = new For($3, $4, $5, (((CompoundStatement*)($7->at(0)))->statements));
				}else{
					$$ = new For($3, $4, $5, *$7);
				}
		 		}
	;

jump_statement
	: RETURN expression ';' {
				$$ = new Return($2);
				std::cerr << "Found return expression;\n";
				}
	| RETURN ';' { $$ = new Return(NULL);}
	;
//	: CONTINUE ';' {}
	| BREAK ';' { $$ = new Break(); }


translation_unit
	: external_declaration { global_root = new Global();
				global_root->statements.insert(global_root->statements.end(), $1->begin(), $1->end());

				//Adds function declarations to declaration map
				if ($1->size() && (*$1)[0]->subtype == "FunctionDeclaration"){
					auto func = (FunctionDeclaration*) (*$1)[0];
					global_root->declaration_map[func->name] = func;
				}
	 			}
	| translation_unit external_declaration {
				global_root->statements.insert(global_root->statements.end(), $2->begin(), $2->end());

				//Adds function declarations to declaration map
				if ($2->size() && (*$2)[0]->subtype == "FunctionDeclaration"){
					auto func = (FunctionDeclaration*) (*$2)[0];
					global_root->declaration_map[func->name] = func;
				}
				}
	;

external_declaration
	: function_definition { $$ = new std::vector<Node*>();
	$$->push_back($1);
	std::cerr << "found global funcdef\n";}
	| declaration {
	std::cerr << "found global declaration\n";
	$$ = $1;}
	;

function_definition
	: declaration_specifiers declarator compound_statement {
	std::cerr<<"found function";
	auto func = (FunctionDeclaration*) $2;
	func->return_type = $1;
	func->statements = *$3;
	$$ = (Node*) func;
	}
	//| declaration_specifiers declarator declaration_list compound_statement {}
	//| declarator declaration_list compound_statement {}
	//| declarator compound_statement {}
	;

%%
#include <stdio.h>

extern char yytext[];

Global* global_root;

Node *parseAST()
{
	global_root=0;
  	yyparse();
  	return global_root;
}


void yyerror(char *s){
	fflush(stdout);
	printf("\n%*s\n%*s\n", "^", s);
}
