#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H

#include "npc.h"
#include <random>
#include <ctime>

class NPCFactory {
private:
    std::mt19937 generator_;
    std::uniform_int_distribution<int> pos_dist_;
    std::uniform_int_distribution<int> type_dist_;

public:
    NPCFactory() 
        : pos_dist_(0, MAP_SIZE), type_dist_(0, 2) {
        std::random_device rd;
        generator_.seed(rd());
    }

    std::shared_ptr<NPC> create_random_npc(int index) {
        int x = pos_dist_(generator_);
        int y = pos_dist_(generator_);
        std::string name = "NPC_" + std::to_string(index);

        switch (type_dist_(generator_)) {
            case 0: return std::make_shared<Elf>(name, x, y);
            case 1: return std::make_shared<Dragon>(name, x, y);
            case 2: return std::make_shared<Druid>(name, x, y);
            default: return nullptr;
        }
    }
};

#endif


