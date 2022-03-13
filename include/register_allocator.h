#ifndef AST_REGISTER_ALLOCATOR_HPP
#define AST_REGISTER_ALLOCATOR_HPP

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>

class RegisterAllocator {
private:
    static std::unordered_map<std::string, int> registersMapping;
    static int currentRegister;
public:
    static void initCurrentRegister();

    static void reinitRegistersMappingMap();

    static int getRegisterNumberForVariable(std::string *variable);

    static std::string intToHex(int i);
};

#endif