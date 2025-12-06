#ifndef BATTLE_VISITOR_H
#define BATTLE_VISITOR_H

#include "npc.h"
#include <memory>
#include <vector>
#include <string>

class Observer;

class BattleVisitor {
private:
    std::vector<std::shared_ptr<Observer>> observers_;
    void notify_observers(const std::string& killer_type, const std::string& killer_name, 
                          const std::string& victim_type, const std::string& victim_name);

public:
    BattleVisitor() = default;
    void add_observer(std::shared_ptr<Observer> obs) {
        observers_.push_back(std::move(obs));
    }

    void visit(Elf& self, std::shared_ptr<NPC> other);
    void visit(Dragon& self, std::shared_ptr<NPC> other);
    void visit(Druid& self, std::shared_ptr<NPC> other);
};

#endif


