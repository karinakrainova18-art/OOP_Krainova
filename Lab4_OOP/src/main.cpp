#include "Point.h"
#include "Figure.h"
#include "Trapeze.h"
#include "Rhombus.h"
#include "Pentagon.h"
#include "Array.h"
#include <iostream>
#include <memory>
#include <limits>
#include <iomanip>

template<ScalarType T>
void printAllFigures(const Array<std::shared_ptr<Figure<T>>>& figures) {
    if (figures.size() == 0) {
        std::cout << "No figures in the array.\n";
        return;
    }
    
    std::cout << "\n=== All Figures ===\n";
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Figure " << i << ": ";
        auto center = figures[i]->geometricCenter();
        std::cout << "Center: " << *center << ", ";
        std::cout << "Vertices: ";
        figures[i]->printVertices(std::cout);
        std::cout << ", Area: " << std::fixed << std::setprecision(2) << figures[i]->area() << std::endl;
    }
}

template<ScalarType T>
double calculateTotalArea(const Array<std::shared_ptr<Figure<T>>>& figures) {
    double total = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total += figures[i]->area();
    }
    return total;
}

void displayMenu() {
    std::cout << "\n=== Figures Program ===\n";
    std::cout << "1. Add Trapeze\n";
    std::cout << "2. Add Rhombus\n";
    std::cout << "3. Add Pentagon\n";
    std::cout << "4. Show All Figures\n";
    std::cout << "5. Remove Figure by Index\n";
    std::cout << "6. Calculate Total Area\n";
    std::cout << "7. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    Array<std::shared_ptr<Figure<int>>> figures;
    
    std::cout << "Template Figures Program\n";
    std::cout << "Using Array<std::shared_ptr<Figure<int>>>\n";
    
    int choice;
    
    do {
        displayMenu();
        std::cin >> choice;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1: {
                auto trap = std::make_shared<Trapeze<int>>();
                std::cout << "Enter trapeze parameters (center_x center_y top_base bottom_base height): ";
                std::cin >> *trap;
                figures.add(trap);
                std::cout << "Trapeze added successfully.\n";
                break;
            }
            case 2: {
                auto rhomb = std::make_shared<Rhombus<int>>();
                std::cout << "Enter rhombus parameters (center_x center_y diagonal1 diagonal2): ";
                std::cin >> *rhomb;
                figures.add(rhomb);
                std::cout << "Rhombus added successfully.\n";
                break;
            }
            case 3: {
                auto pent = std::make_shared<Pentagon<int>>();
                std::cout << "Enter pentagon parameters (center_x center_y radius): ";
                std::cin >> *pent;
                figures.add(pent);
                std::cout << "Pentagon added successfully.\n";
                break;
            }
            case 4:
                printAllFigures(figures);
                break;
            case 5: {
                size_t index;
                std::cout << "Enter index of figure to remove: ";
                std::cin >> index;
                if (index < figures.size()) {
                    figures.remove(index);
                    std::cout << "Figure removed successfully.\n";
                } else {
                    std::cout << "Invalid index.\n";
                }
                break;
            }
            case 6:
                std::cout << "Total area of all figures: " 
                          << std::fixed << std::setprecision(2) 
                          << calculateTotalArea(figures) << std::endl;
                break;
            case 7:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 7);
    
    std::cout << "\n=== Demonstration: Array<Rhombus<int>> ===\n";
    Array<std::shared_ptr<Rhombus<int>>> rhombusArray;
    
    auto rhomb1 = std::make_shared<Rhombus<int>>(0, 0, 4, 6);
    auto rhomb2 = std::make_shared<Rhombus<int>>(5, 5, 8, 10);
    
    rhombusArray.add(rhomb1);
    rhombusArray.add(rhomb2);
    
    std::cout << "Rhombus array size: " << rhombusArray.size() << std::endl;
    for (size_t i = 0; i < rhombusArray.size(); ++i) {
        std::cout << "Rhombus " << i << " area: " << rhombusArray[i]->area() << std::endl;
    }
    
    std::cout << "\n=== Demonstration: Conversion to double ===\n";
    auto trap = std::make_shared<Trapeze<int>>(0, 0, 2, 4, 3);
    double area = static_cast<double>(*trap);
    std::cout << "Trapeze area (via conversion): " << area << std::endl;
    
    std::cout << "\n=== Demonstration: Comparison ===\n";
    auto trap1 = std::make_shared<Trapeze<int>>(0, 0, 2, 4, 3);
    auto trap2 = std::make_shared<Trapeze<int>>(0, 0, 2, 4, 3);
    auto trap3 = std::make_shared<Trapeze<int>>(1, 1, 2, 4, 3);
    
    std::cout << "trap1 == trap2: " << (*trap1 == *trap2) << std::endl;
    std::cout << "trap1 == trap3: " << (*trap1 == *trap3) << std::endl;
    
    return 0;
}
