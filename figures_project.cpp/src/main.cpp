#include "Figure.h"
#include "Rectangle.h"
#include "Trapeze.h"
#include "Rhombus.h"
#include <iostream>
#include <memory>
#include <limits>

void displayMenu() {
    std::cout << "\n=== Figures Program ===\n";
    std::cout << "1. Add Rectangle\n";
    std::cout << "2. Add Trapeze\n";
    std::cout << "3. Add Rhombus\n";
    std::cout << "4. Show All Figures\n";
    std::cout << "5. Remove Figure by Index\n";
    std::cout << "6. Calculate Total Area\n";
    std::cout << "7. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    FigureArray figures;
    int choice;
    
    std::cout << "Rotation Figures Program\n";
    
    do {
        displayMenu();
        std::cin >> choice;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1: {
                auto rect = std::make_unique<Rectangle>();
                std::cout << "Enter rectangle parameters (center_x center_y width height): ";
                std::cin >> *rect;
                figures.addFigure(std::move(rect));
                std::cout << "Rectangle added successfully.\n";
                break;
            }
            case 2: {
                auto trap = std::make_unique<Trapeze>();
                std::cout << "Enter trapeze parameters (center_x center_y top_base bottom_base height): ";
                std::cin >> *trap;
                figures.addFigure(std::move(trap));
                std::cout << "Trapeze added successfully.\n";
                break;
            }
            case 3: {
                auto rhomb = std::make_unique<Rhombus>();
                std::cout << "Enter rhombus parameters (center_x center_y diagonal1 diagonal2): ";
                std::cin >> *rhomb;
                figures.addFigure(std::move(rhomb));
                std::cout << "Rhombus added successfully.\n";
                break;
            }
            case 4:
                if (figures.size() == 0) {
                    std::cout << "No figures in the array.\n";
                } else {
                    std::cout << "\nAll Figures:\n";
                    figures.printAll();
                }
                break;
            case 5: {
                size_t index;
                std::cout << "Enter index of figure to remove: ";
                std::cin >> index;
                if (index < figures.size()) {
                    figures.removeFigure(index);
                    std::cout << "Figure removed successfully.\n";
                } else {
                    std::cout << "Invalid index.\n";
                }
                break;
            }
            case 6:
                std::cout << "Total area of all figures: " << figures.totalArea() << std::endl;
                break;
            case 7:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 7);
    
    return 0;
}