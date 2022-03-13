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
    static void initCurrentRegister() {
        currentRegister = 2;
    }

    static void reinitRegistersMappingMap() {
        std::unordered_map<std::string, int> map;
        registersMapping = map;
    }

    static int getRegisterNumberForVariable(std::string *variable) {
        int result = currentRegister;
        auto iterator = registersMapping.find(*variable);
        if (iterator == registersMapping.end()) {
            registersMapping.insert(std::pair<std::string, int>(*variable, currentRegister));
        } else {
            result = iterator->second;
        }
        currentRegister++;
        return result;
    }

    static std::string intToHex(int i) {
        std::stringstream stream;
        stream << "0x" << std::setfill('0') << std::setw(sizeof(i)) << std::hex << i;
        return stream.str();
    }
};

int RegisterAllocator::currentRegister = 0;
std::unordered_map<std::string, int> map;
std::unordered_map<std::string, int> RegisterAllocator::registersMapping = map;
#endif