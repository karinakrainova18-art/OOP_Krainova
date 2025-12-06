#include "../include/battle_visitor.h"
#include "../include/observer.h"

void BattleVisitor::notify_observers(const std::string& killer_type, const std::string& killer_name,
                                     const std::string& victim_type, const std::string& victim_name) {
    std::string event = killer_type + " (" + killer_name + ") killed " + victim_type + " (" + victim_name + ")";
    for (const auto& obs : observers_) {
        obs->update(event);
    }
}


void BattleVisitor::visit(Dragon& self, std::shared_ptr<NPC> other) {
    if (other->get_type() == "Elf") {
        other->set_dead();
        notify_observers(self.get_type(), self.get_name(), other->get_type(), other->get_name());
    }
}

void BattleVisitor::visit(Elf& self, std::shared_ptr<NPC> other) {
    if (other->get_type() == "Druid") {
        other->set_dead();
        notify_observers(self.get_type(), self.get_name(), other->get_type(), other->get_name());
    }
}

void BattleVisitor::visit(Druid& self, std::shared_ptr<NPC> other) {
    if (other->get_type() == "Dragon") {
        other->set_dead();
        notify_observers(self.get_type(), self.get_name(), other->get_type(), other->get_name());
    }
}


