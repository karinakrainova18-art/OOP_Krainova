#include "../include/dungeon_editor.h"
#include <fstream>
#include <algorithm>
#include <iomanip>

DungeonEditor::DungeonEditor() {
    battle_visitor_.add_observer(std::make_shared<ConsoleObserver>());
    battle_visitor_.add_observer(std::make_shared<FileObserver>("log.txt"));
    std::cout << "Editor initialized. Observers (Console, log.txt) registered.\n";
}

bool DungeonEditor::add_npc(const std::string& type, const std::string& name, int x, int y) {
    std::shared_ptr<NPC> new_npc = factory_.create_npc(type, name, x, y);
    if (new_npc) {
        for (const auto& npc : npcs_) {
            if (npc->get_name() == name) {
                std::cerr << "Error: NPC with name '" << name << "' already exists. Cannot add.\n";
                return false;
            }
        }
        npcs_.push_back(new_npc);
        return true;
    }
    return false;
}

bool DungeonEditor::save(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for saving: " << filename << std::endl;
        return false;
    }
    for (const auto& npc : npcs_) {
        if (npc->is_alive()) { 
            file << npc->to_file_string() << "\n";
        }
    }
    std::cout << "Successfully saved " << npcs_.size() << " NPC(s) to " << filename << std::endl;
    return true;
}

bool DungeonEditor::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for loading: " << filename << std::endl;
        return false;
    }
    
    npcs_.clear();
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::shared_ptr<NPC> new_npc = factory_.create_npc_from_file_string(line);
        if (new_npc) {
            npcs_.push_back(new_npc);
            count++;
        } else {
            std::cerr << "Warning: Skipping invalid line during loading: " << line << std::endl;
        }
    }
    std::cout << "Successfully loaded " << count << " NPC(s) from " << filename << std::endl;
    return true;
}

void DungeonEditor::print_npcs() const {
    if (npcs_.empty()) {
        std::cout << "Dungeon is empty.\n";
        return;
    }
    std::cout << "\n--- NPC Roster (" << npcs_.size() << " total) ---\n";
    std::cout << std::left << std::setw(10) << "Status" << std::setw(15) << "Type" << std::setw(15) << "Name" << "Coordinates\n";
    std::cout << std::string(50, '-') << "\n";
    for (const auto& npc : npcs_) {
        std::cout << std::left << std::setw(10) << (npc->is_alive() ? "ALIVE" : "DEAD")
                  << std::setw(15) << npc->get_type()
                  << std::setw(15) << npc->get_name()
                  << "(" << npc->get_x() << ", " << npc->get_y() << ")\n";
    }
    std::cout << "-----------------------------------\n";
}

void DungeonEditor::remove_dead_npcs() {
    auto initial_size = npcs_.size();
    npcs_.erase(std::remove_if(npcs_.begin(), npcs_.end(), 
                               [](const auto& npc) { return !npc->is_alive(); }), 
                               npcs_.end());
    if (initial_size > npcs_.size()) {
        std::cout << initial_size - npcs_.size() << " NPC(s) removed from the dungeon.\n";
    }
}

void DungeonEditor::run_battle(double max_distance) {
    std::cout << "\n--- Entering Battle Mode (Range: " << max_distance << ") ---\n";
    size_t initial_count = npcs_.size();
    
    for (size_t i = 0; i < npcs_.size(); ++i) {
        for (size_t j = i + 1; j < npcs_.size(); ++j) {
            
            auto npc1 = npcs_[i];
            auto npc2 = npcs_[j];
            if (!npc1->is_alive() || !npc2->is_alive()) {
                continue; 
            }
            if (NPC::distance(npc1, npc2) <= max_distance) {
                std::cout << "Clash: " << npc1->get_name() << " vs " << npc2->get_name() 
                          << " (Distance: " << std::fixed << std::setprecision(2) << NPC::distance(npc1, npc2) << ")\n";
                
                npc1->accept(battle_visitor_, npc2);
            }
        }
    }
    remove_dead_npcs();
    std::cout << "--- Battle Finished. Remaining: " << npcs_.size() << " NPC(s) ---\n\n";
}


