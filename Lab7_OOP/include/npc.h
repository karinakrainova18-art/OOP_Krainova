#ifndef NPC_H
#define NPC_H

#include <iostream>
#include <string>
#include <memory>
#include <cmath>
#include <vector>
#include <mutex>
#include <random>

constexpr int MAP_SIZE = 100;
constexpr int INITIAL_NPC_COUNT = 50;
constexpr int SIMULATION_DURATION_SEC = 30;

class BattleLogic;

struct NpcStats {
    int move_distance;      
    int kill_distance;      
};

class NPC : public std::enable_shared_from_this<NPC> {
protected:
    std::string name_;
    int x_, y_;
    int health_;
    const NpcStats stats_;
    mutable std::mutex pos_mutex_; 

public:
    NPC(const std::string& name, int x, int y, NpcStats stats) 
        : name_(name), x_(x), y_(y), health_(1), stats_(stats) {}
    virtual ~NPC() = default;

    const std::string& get_name() const { return name_; }
    virtual std::string get_type() const = 0;
    const NpcStats& get_stats() const { return stats_; }
    bool is_alive() const { return health_ == 1; }
    void set_dead() { health_ = 0; }

    void get_position(int& x, int& y) const {
        std::lock_guard<std::mutex> lock(pos_mutex_);
        x = x_;
        y = y_;
    }

    void move(int dx, int dy) {
        std::lock_guard<std::mutex> lock(pos_mutex_);
        
        int new_x = x_ + dx;
        int new_y = y_ + dy;
        x_ = std::max(0, std::min(MAP_SIZE, new_x));
        y_ = std::max(0, std::min(MAP_SIZE, new_y));
    }
    
    virtual void accept_attack(BattleLogic& visitor, std::shared_ptr<NPC> other) = 0;
    virtual char get_symbol() const = 0;
};

class Elf : public NPC {
public:
    Elf(const std::string& name, int x, int y) 
        : NPC(name, x, y, {10, 50}) {}  
    void accept_attack(BattleLogic& visitor, std::shared_ptr<NPC> other) override;
    std::string get_type() const override { return "Elf"; }
    char get_symbol() const override { return 'E'; }
};

class Dragon : public NPC {
public:
    Dragon(const std::string& name, int x, int y) 
        : NPC(name, x, y, {50, 30}) {} 
    void accept_attack(BattleLogic& visitor, std::shared_ptr<NPC> other) override;
    std::string get_type() const override { return "Dragon"; }
    char get_symbol() const override { return 'D'; }
};

class Druid : public NPC {
public:
    Druid(const std::string& name, int x, int y) 
        : NPC(name, x, y, {10, 10}) {}  
    void accept_attack(BattleLogic& visitor, std::shared_ptr<NPC> other) override;
    std::string get_type() const override { return "Druid"; }
    char get_symbol() const override { return 'R'; }
};

static double distance_sq(std::shared_ptr<const NPC> a, std::shared_ptr<const NPC> b) {
    int ax, ay, bx, by;
    a->get_position(ax, ay);
    b->get_position(bx, by);
    return std::pow(static_cast<double>(ax - bx), 2) + std::pow(static_cast<double>(ay - by), 2);
}

#endif


