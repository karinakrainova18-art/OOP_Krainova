#ifndef DUNGEON_EDITOR_H
#define DUNGEON_EDITOR_H

#include "npc.h"
#include "npc_factory.h"
#include "battle_visitor.h"
#include "observer.h"
#include <vector>
#include <string>
#include <memory>

class DungeonEditor {
private:
    std::vector<std::shared_ptr<NPC>> npcs_;
    NPCFactory factory_;
    BattleVisitor battle_visitor_;
    void remove_dead_npcs();

public:
    DungeonEditor();
    bool add_npc(const std::string& type, const std::string& name, int x, int y);
    bool save(const std::string& filename) const;
    bool load(const std::string& filename);
    void print_npcs() const;
    void run_battle(double max_distance);
};

#endif


