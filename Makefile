  
CPPFLAGS += -std=c++17 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I inc

bin/c_compiler : bin/compiler src/wrapper.sh
	cp src/wrapper.sh bin/c_compiler
	chmod u+x bin/c_compiler

bin/compiler : src/compiler.cpp
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/compiler $^

lexer : src/lexer.flex test/lexer_main.cpp src/lexer.hpp
	mkdir -p bin
	flex -o bin/lexer.yy.cpp src/lexer.flex
	cp -r src/lexer.hpp bin/lexer.hpp
	g++ $(CPPFLAGS) -c bin/lexer.yy.cpp -o bin/lexer.yy.o
	g++ $(CPPFLAGS) -c test/lexer_main.cpp -o bin/lexer_main.o
	g++ $(CPPFLAGS) -o bin/lexer bin/lexer.yy.o bin/lexer_main.o

src/maths_parser.tab.cpp src/maths_parser.tab.hpp : src/maths_parser.y
	bison -v -d src/maths_parser.y -o src/maths_parser.tab.cpp

src/maths_lexer.yy.cpp : src/maths_lexer.flex src/maths_parser.tab.hpp
	flex -o src/maths_lexer.yy.cpp  src/maths_lexer.flex

parser : src/lexer.flex src/lexer.hpp test/parser_test.cpp src/ast.hpp src/ast
	mkdir -p bin
	flex -o bin/lexer.yy.cpp src/lexer.flex
	cp -r src/lexer.hpp bin/lexer.hpp
	cp -r src/ast.hpp bin/ast.hpp
	cp -r src/ast bin/ast
	cp -r test/parser_test.cpp bin/parser_test.cpp
	bison -v -d src/parser.y -o bin/parser.tab.cpp
	g++ $(CPPFLAGS) -c bin/lexer.yy.cpp -o bin/lexer.yy.o
	g++ $(CPPFLAGS) -c bin/parser.tab.cpp -o bin/parser.tab.o
	g++ $(CPPFLAGS) -c bin/parser_test.cpp -o bin/parser_test.o
	g++ $(CPPFLAGS) -o bin/parser bin/parser_test.o bin/parser.tab.o bin/lexer.yy.o

clean :
	rm -f */*.yy.cpp
	rm -f test/out/*
	rm -f src/*.o
	rm -r bin