#include "include/dungeon_editor.h"
#include <sstream>
#include <limits>

void show_menu() {
    std::cout << "\n--- Balagur Fate 3 Dungeon Editor ---\n";
    std::cout << "1. Add NPC (Type Name X Y)\n";
    std::cout << "2. Save to file\n";
    std::cout << "3. Load from file\n";
    std::cout << "4. Print NPC list\n";
    std::cout << "5. Run Battle (Range)\n";
    std::cout << "6. Exit\n";
    std::cout << "-------------------------------------\n";
    std::cout << "Enter command: ";
}

void clear_input_buffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    DungeonEditor editor;
    std::string line;
    int choice;

    while (true) {
        show_menu();
        if (!(std::cin >> choice)) {
            std::cerr << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: {
                std::string type, name;
                int x, y;
                std::cout << "Enter Type (Elf, Dragon, Druid), Name, X, Y: ";
                if (std::cin >> type >> name >> x >> y) {
                    editor.add_npc(type, name, x, y);
                } else {
                    std::cerr << "Invalid format.\n";
                    std::cin.clear();
                    clear_input_buffer();
                }
                break;
            }
            case 2: {
                std::string filename = "dungeon_save.txt";
                editor.save(filename);
                break;
            }
            case 3: {
                std::string filename = "dungeon_save.txt";
                editor.load(filename);
                break;
            }
            case 4: {
                editor.print_npcs();
                break;
            }
            case 5: {
                double range;
                std::cout << "Enter battle range (double): ";
                if (std::cin >> range) {
                    editor.run_battle(range);
                } else {
                    std::cerr << "Invalid range format.\n";
                    std::cin.clear();
                    clear_input_buffer();
                }
                break;
            }
            case 6: {
                std::cout << "Exiting editor. Goodbye!\n";
                return 0;
            }
            default:
                std::cout << "Unknown command. Try again.\n";
                break;
        }
    }
    return 0;
}


