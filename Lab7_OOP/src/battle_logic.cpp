#include "../include/battle_logic.h"
#include <iostream>
#include <algorithm>
#include <thread>

static void safe_cout(std::mutex& cout_mutex, const std::string& message) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << message << std::endl;
}

void BattleLogic::perform_attack(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender) {
    if (!attacker->is_alive() || !defender->is_alive()) return;

    int attack_roll = dice_.roll();
    int defense_roll = dice_.roll();

    std::string log_msg = attacker->get_name() + " (" + attacker->get_type() + ") attacks " + 
                          defender->get_name() + " (" + defender->get_type() + "). " +
                          "Attack: " + std::to_string(attack_roll) + ", Defense: " + std::to_string(defense_roll) + ".";

    if (attack_roll > defense_roll) {
        defender->set_dead();
        log_msg += " -> VICTORY! " + defender->get_name() + " killed.";
    } else {
        log_msg += " -> Missed.";
    }

    safe_cout(cout_mutex_, log_msg);
}

void BattleLogic::start_battle(std::shared_ptr<NPC> npc1, std::shared_ptr<NPC> npc2) {
    if (npc1->is_alive() && npc2->is_alive()) {
        npc1->accept_attack(*this, npc2);
    }
    
    if (npc1->is_alive() && npc2->is_alive()) {
        npc2->accept_attack(*this, npc1);
    }
}


void BattleLogic::visit_attack(Dragon& self, std::shared_ptr<NPC> other) {
    if (other->get_type() == "Elf") {
        perform_attack(self.shared_from_this(), other);
    }
}

void BattleLogic::visit_attack(Elf& self, std::shared_ptr<NPC> other) {
    if (other->get_type() == "Druid") {
        perform_attack(self.shared_from_this(), other);
    }
}

void BattleLogic::visit_attack(Druid& self, std::shared_ptr<NPC> other) {
    if (other->get_type() == "Dragon") {
        perform_attack(self.shared_from_this(), other);
    }
}


