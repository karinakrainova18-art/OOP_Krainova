#pragma once
#include <string>
#include <stdexcept>

class BracketValidator {
public:
    static bool isValid(const std::string& brackets);
    
    static size_t getMaxInputLength();
    static std::string getAllowedCharacters();
    
private:
    static const size_t MAX_LENGTH = 100;
    static const char OPEN_BRACKET = '(';
    static const char CLOSE_BRACKET = ')';
    
    static void validateInput(const std::string& brackets);
    static bool isEmpty(const std::string& str);
};