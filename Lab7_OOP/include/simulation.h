#ifndef SIMULATION_H
#define SIMULATION_H

#include "npc.h"
#include "npc_factory.h"
#include "battle_logic.h"
#include <vector>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <condition_variable>

class Simulation {
private:
    std::vector<std::shared_ptr<NPC>> npcs_;
    NPCFactory factory_;
    mutable std::shared_mutex npcs_mutex_;
    mutable std::mutex cout_mutex_;       
    std::atomic<bool> running_{false};
    std::thread move_thread_;
    std::thread battle_thread_;
    std::thread main_thread_;

    struct BattleTask {
        std::shared_ptr<NPC> npc1;
        std::shared_ptr<NPC> npc2;
    };

    std::vector<BattleTask> battle_queue_;
    std::mutex queue_mutex_;
    std::condition_variable queue_cv_;
    BattleLogic battle_logic_;

    void move_and_detect_thread_func();
    void battle_thread_func();
    void main_print_thread_func();

public:
    Simulation();
    ~Simulation();
    void start();
    void stop();
    void print_survivors() const;
    bool is_running() const { return running_.load(); }
};

#endif


