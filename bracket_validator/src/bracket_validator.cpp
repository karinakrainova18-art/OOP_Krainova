#include "bracket_validator.h"
#include <string>

bool BracketValidator::isValid(const std::string& brackets) {
    validateInput(brackets);
    
    if (isEmpty(brackets)) {
        return true;
    }
    
    int balance = 0;
    
    for (char c : brackets) {
        if (c == OPEN_BRACKET) {
            balance++;
        } else if (c == CLOSE_BRACKET) {
            balance--;
            if (balance < 0) {
                return false;
            }
        }
    }
    
    return balance == 0;
}

void BracketValidator::validateInput(const std::string& brackets) {
    if (brackets.length() > MAX_LENGTH) {
        throw std::invalid_argument("Input string too long");
    }
    
    for (char c : brackets) {
        if (c != OPEN_BRACKET && c != CLOSE_BRACKET) {
            throw std::invalid_argument("Invalid character in input");
        }
    }
}

bool BracketValidator::isEmpty(const std::string& str) {
    return str.empty();
}

size_t BracketValidator::getMaxInputLength() {
    return MAX_LENGTH;
}

std::string BracketValidator::getAllowedCharacters() {
    return std::string(1, OPEN_BRACKET) + std::string(1, CLOSE_BRACKET);
}