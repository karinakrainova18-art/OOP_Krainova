#ifndef NPC_H
#define NPC_H

#include <iostream>
#include <string>
#include <memory>
#include <cmath>
#include <vector>

class BattleVisitor;

class NPC : public std::enable_shared_from_this<NPC> {
protected:
    std::string name_;
    int x_, y_;
    int health_;

public:
    NPC(const std::string& name, int x, int y) : name_(name), x_(x), y_(y), health_(1) {}
    virtual ~NPC() = default;

    const std::string& get_name() const { return name_; }
    int get_x() const { return x_; }
    int get_y() const { return y_; }
    int is_alive() const { return health_; }
    void set_dead() { health_ = 0; }
    
    virtual void accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) = 0;
    virtual std::string get_type() const = 0;
    virtual std::string to_string() const;
    virtual std::string to_file_string() const;

    static double distance(std::shared_ptr<const NPC> a, std::shared_ptr<const NPC> b) {
        return std::sqrt(std::pow(a->x_ - b->x_, 2) + std::pow(a->y_ - b->y_, 2));
    }
};

class Elf : public NPC {
public:
    Elf(const std::string& name, int x, int y) : NPC(name, x, y) {}
    void accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) override;
    std::string get_type() const override { return "Elf"; }
};

class Dragon : public NPC {
public:
    Dragon(const std::string& name, int x, int y) : NPC(name, x, y) {}
    void accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) override;
    std::string get_type() const override { return "Dragon"; }
};

class Druid : public NPC {
public:
    Druid(const std::string& name, int x, int y) : NPC(name, x, y) {}
    void accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) override;
    std::string get_type() const override { return "Druid"; }
};

#endif


