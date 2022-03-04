  
CPPFLAGS += -std=c++2a -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I inc

all : bin/c_compiler src/lexer.yy.cpp src/parser.tab.cpp

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

src/parser.tab.cpp src/parser.tab.hpp : src/parser.y
	bison -v -d src/parser.y -o src/parser.tab.cpp

clean :
	rm -f src/*.o
	rm -f bin/*
	rm -f src/*.tab.cpp
	rm -f src/*.tab.hpp
	rm -f src/*.yy.cpp
	rm -f src/*.output
	rm -f test/out/*