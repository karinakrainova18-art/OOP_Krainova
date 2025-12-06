#include "../include/npc.h"
#include "../include/battle_visitor.h"
#include <sstream>

std::string NPC::to_string() const {
    std::stringstream ss;
    ss << "[" << (is_alive() ? "ALIVE" : "DEAD") << "] "
       << get_type() << " (" << name_ << ") at (" << x_ << ", " << y_ << ")";
    return ss.str();
}

std::string NPC::to_file_string() const {
    std::stringstream ss;
    ss << get_type() << "|" << name_ << "|" << x_ << "|" << y_;
    return ss.str();
}

void Elf::accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) {
    visitor.visit(*this, other);
}

void Dragon::accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) {
    visitor.visit(*this, other);
}

void Druid::accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) {
    visitor.visit(*this, other);
}


