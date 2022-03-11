  
CPPFLAGS += -std=c++2a -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I inc

all : bin/c_compiler src/lexer.yy.cpp src/parser.tab.cpp

bin/c_compiler : bin/compiler src/wrapper.sh
	cp src/wrapper.sh bin/c_compiler
	chmod u+x bin/c_compiler

bin/compiler : src/compiler.cpp lexer parser
	mkdir -p bin
	g++ $(CPPFLAGS) -c src/compiler.cpp -o build/compiler.o
	g++ $(CPPFLAGS) -o bin/compiler build/lexer.yy.o build/parser.tab.o build/compiler.o

lexer : src/lexer.flex parser
	mkdir -p build
	flex -o build/lexer.yy.cpp src/lexer.flex
	g++ $(CPPFLAGS) -c build/lexer.yy.cpp -o build/lexer.yy.o

parser : src/parser.y  include/ast.hpp
	mkdir -p build
	bison -v -d src/parser.y -o build/parser.tab.cpp
	g++ $(CPPFLAGS) -c build/parser.tab.cpp -o build/parser.tab.o

lexertest : parser lexer test_lexer/src/lexer_main.cpp
	g++ $(CPPFLAGS) -o test_lexer/bin/lexer_test.o test_lexer/src/lexer_main.cpp build/lexer.yy.o

parsertest : parser lexer test_parser/src/parser_main.cpp
	g++ $(CPPFLAGS) -o test_parser/bin/parser_test.o test_parser/src/parser_main.cpp build/lexer.yy.o build/parser.tab.o

codegentest : test_codegen/src/codegen_main.cpp
	g++ $(CPPFLAGS) -o test_codegen/bin/codegen_main test_codegen/src/codegen_main.cpp

clean :
	rm -f src/*.o
	rm -f bin/*
	rm -f build/*
	rm -f src/*.tab.cpp
	rm -f src/*.tab.hpp
	rm -f src/*.yy.cpp
	rm -f src/*.output
	rm -f test/out/*