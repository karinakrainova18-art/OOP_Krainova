#include <iostream>
#include <string>
#include "bracket_validator.h"

int main() {
    std::cout << "=== Bracket Validator ===" << std::endl;
    std::cout << "Max input length: " << BracketValidator::getMaxInputLength() << std::endl;
    std::cout << "Allowed characters: " << BracketValidator::getAllowedCharacters() << std::endl;
    std::cout << "Enter 'stop' to exit" << std::endl << std::endl;
    
    std::string input;
    while (true) {
        std::cout << "Enter bracket sequence: ";
        std::getline(std::cin, input);
        
        if (input == "stop") {
            break;
        }
        
        try {
            bool isValid = BracketValidator::isValid(input);
            std::cout << "Result: " << (isValid ? "VALID" : "INVALID") << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        
        std::cout << std::endl;
    }
    
    std::cout << "Goodbye!" << std::endl;
    return 0;
}