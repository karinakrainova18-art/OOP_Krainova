#include "../include/npc_factory.h"
#include <vector>

NPCFactory::NPCFactory() {
    factory_methods_["Elf"] = [](const std::string& name, int x, int y) {
        return std::make_shared<Elf>(name, x, y);
    };
    factory_methods_["Dragon"] = [](const std::string& name, int x, int y) {
        return std::make_shared<Dragon>(name, x, y);
    };
    factory_methods_["Druid"] = [](const std::string& name, int x, int y) {
        return std::make_shared<Druid>(name, x, y);
    };
}

std::shared_ptr<NPC> NPCFactory::create_npc(const std::string& type, const std::string& name, int x, int y) {
    if (factory_methods_.count(type)) {
        if (x < 0 || x > 500 || y < 0 || y > 500) {
            std::cerr << "Error: Coordinates (" << x << ", " << y << ") out of bounds [0, 500].\n";
            return nullptr;
        }
        return factory_methods_[type](name, x, y);
    }
    std::cerr << "Error: Unknown NPC type: " << type << "\n";
    return nullptr;
}

std::shared_ptr<NPC> NPCFactory::create_npc_from_file_string(const std::string& file_string) {
    std::stringstream ss(file_string);
    std::string segment;
    std::vector<std::string> parts;
    while (std::getline(ss, segment, '|')) {
        parts.push_back(segment);
    }
    if (parts.size() != 4) {
        std::cerr << "Error: Invalid file format.\n";
        return nullptr;
    }
    const std::string& type = parts[0];
    const std::string& name = parts[1];
    try {
        int x = std::stoi(parts[2]);
        int y = std::stoi(parts[3]);
        
        return create_npc(type, name, x, y);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing coordinates from file: " << e.what() << "\n";
        return nullptr;
    }
}

