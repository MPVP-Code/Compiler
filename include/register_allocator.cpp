#include "register_allocator.h"

int RegisterAllocator::currentRegister = 0;
std::unordered_map<std::string, int> map;
std::unordered_map<std::string, int> RegisterAllocator::registersMapping = map;

void RegisterAllocator::initCurrentRegister() {
    RegisterAllocator::currentRegister = 2;
}

void RegisterAllocator::reinitRegistersMappingMap() {
    std::unordered_map<std::string, int> map;
    registersMapping = map;
}

int RegisterAllocator::getRegisterNumberForVariable(std::string *variable)  {
    int result = currentRegister;
    auto iterator = registersMapping.find(*variable);
    if (iterator == registersMapping.end()) {
        registersMapping.insert(std::pair<std::string, int>(*variable, currentRegister));
        currentRegister++;
    } else {
        result = iterator->second;
    }
    return result;
}

std::string RegisterAllocator::intToHex(int i)  {
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(i)) << std::hex << i;
    return stream.str();
}