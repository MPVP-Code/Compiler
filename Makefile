  
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

clean :
	rm -f */*.yy.cpp
	rm -f test/out/*
	rm -f src/*.o
	rm -f bin/*