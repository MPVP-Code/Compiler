  
CPPFLAGS += -std=c++2a -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I inc

ASTOUT := include/register_allocator.o include/ast/ast_arithmetic.o include/ast/ast_assignment.o include/ast/ast_bitwise.o include/ast/ast_flow_control.o include/ast/ast_func.o include/ast/ast_jump_statement.o include/ast/ast_logic.o include/ast/ast_node.o include/ast/ast_scope.o include/ast/ast_syntax.o include/ast/ast_variable.o
AST := include/register_allocator.cpp include/ast/ast_arithmetic.cpp include/ast/ast_assignment.cpp include/ast/ast_bitwise.cpp include/ast/ast_flow_control.cpp include/ast/ast_func.cpp include/ast/ast_jump_statement.cpp include/ast/ast_logic.cpp include/ast/ast_node.cpp include/ast/ast_scope.cpp include/ast/ast_syntax.cpp include/ast/ast_variable.cpp

all : bin/c_compiler src/lexer.yy.cpp src/parser.tab.cpp

bin/c_compiler : bin/compiler src/wrapper.sh
	cp src/wrapper.sh bin/c_compiler
	chmod u+x bin/c_compiler

bin/compiler : src/compiler.cpp lexer $(AST)
	mkdir -p bin
	g++ $(CPPFLAGS) -c src/compiler.cpp -o build/compiler.o
	g++ $(CPPFLAGS) -o bin/compiler build/lexer.yy.o build/parser.tab.o build/compiler.o $(AST)

syntax_test: src/syntax_test.cpp $(AST)
	g++ $(CPPFLAGS) -o bin/syntax_test src/syntax_test.cpp $(AST)

lexer : src/lexer.flex parser
	mkdir -p build
	flex -o build/lexer.yy.cpp src/lexer.flex
	g++ $(CPPFLAGS) -c build/lexer.yy.cpp -o build/lexer.yy.o

parser : src/parser.y  include/ast.hpp include/register_allocator.cpp
	mkdir -p build
	bison -v -d src/parser.y -o build/parser.tab.cpp
	g++ $(CPPFLAGS) -c build/parser.tab.cpp -o build/parser.tab.o

lexertest : parser lexer test_lexer/src/lexer_main.cpp include/register_allocator.cpp
	mkdir -p test_lexer/bin
	g++ $(CPPFLAGS) -o test_lexer/bin/lexer_test.o test_lexer/src/lexer_main.cpp build/lexer.yy.o include/register_allocator.cpp

parsertest : parser lexer test_parser/src/parser_main.cpp $(ASTOUT)
	mkdir -p test_parser/bin
	g++ $(CPPFLAGS) -o test_parser/bin/parsertest test_parser/src/parser_main.cpp build/lexer.yy.o build/parser.tab.o $(ASTOUT)

codegentest : test_codegen/src/codegen_main.cpp include/register_allocator.cpp
	g++ $(CPPFLAGS) -o test_codegen/bin/codegen_main test_codegen/src/codegen_main.cpp include/register_allocator.cpp

clean :
	rm -f src/*.o
	rm -f include/**/*.o
	rm -f bin/*
	rm -f build/*
	rm -f src/*.tab.cpp
	rm -f src/*.tab.hpp
	rm -f src/*.yy.cpp
	rm -f src/*.output
	rm -f test/out/*