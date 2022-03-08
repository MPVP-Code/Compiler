#include<iostream>
#include <iomanip>
#include "../include/ast.hpp"
#include "../build/parser.tab.hpp"

int main(int argc, char *argv[])
{
//    if(argc < 2){
//        fprintf(stderr, "usage : compiler sourceCode\n");
//        exit(1);
//    }
//
//    //std::ifstream src(argv[1]);
//    if(!src.is_open()){
//        fprintf(stderr, "Couldn't open '%s'\n", argv[1]);
//        exit(1);
//    }
//
//    //TreePtr tree=Parse(src);
//
//    //Compile(tree);
//
//    return 0;

while (1){
    int s = yylex();
    std::cout << s << std::endl;
}
}
