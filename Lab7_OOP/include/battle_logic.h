#ifndef BATTLE_LOGIC_H
#define BATTLE_LOGIC_H

#include "npc.h"
#include <mutex>
#include <random>

class Dice {
private:
    std::mt19937 generator_;
    std::uniform_int_distribution<int> distribution_;

public:
    Dice() : distribution_(1, 6) {
        std::random_device rd;
        generator_.seed(rd());
    }

    int roll() {
        return distribution_(generator_);
    }
};

class BattleLogic {
private:
    Dice dice_;
    std::mutex& cout_mutex_;
    void perform_attack(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender);

public:
    BattleLogic(std::mutex& cout_mutex) : cout_mutex_(cout_mutex) {}
    void start_battle(std::shared_ptr<NPC> npc1, std::shared_ptr<NPC> npc2);
    void visit_attack(Elf& self, std::shared_ptr<NPC> other);
    void visit_attack(Dragon& self, std::shared_ptr<NPC> other);
    void visit_attack(Druid& self, std::shared_ptr<NPC> other);
};

inline void Elf::accept_attack(BattleLogic& visitor, std::shared_ptr<NPC> other) {
    visitor.visit_attack(*this, other);
}

inline void Dragon::accept_attack(BattleLogic& visitor, std::shared_ptr<NPC> other) {
    visitor.visit_attack(*this, other);
}

inline void Druid::accept_attack(BattleLogic& visitor, std::shared_ptr<NPC> other) {
    visitor.visit_attack(*this, other);
}

#endif


