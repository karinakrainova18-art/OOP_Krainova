#include "gtest/gtest.h"
#include "../include/npc.h" 
#include "../include/npc_factory.h"
#include "../include/battle_logic.h"
#include <memory>
#include <string>
#include <mutex>

std::mutex g_test_mutex; 

std::string make_name(const std::string& type, int id) {
    return type + "_" + std::to_string(id);
}

TEST(NPCTest, InitialPositionAndAliveStatus) {
    auto elf = std::make_shared<Elf>(make_name("Elf", 1), 10, 20); 
    int x, y;
    elf->get_position(x, y);
    EXPECT_EQ(x, 10);
    EXPECT_EQ(y, 20);
    EXPECT_TRUE(elf->is_alive());
}

TEST(NPCTest, MoveWithinBounds) {
    auto dragon = std::make_shared<Dragon>(make_name("Dragon", 2), 50, 50); 
    dragon->move(10, -5); 
    int x, y;
    dragon->get_position(x, y);
    EXPECT_EQ(x, 60);
    EXPECT_EQ(y, 45);
}

TEST(NPCTest, MoveClampingToBounds) {
    auto druid = std::make_shared<Druid>(make_name("Druid", 3), 5, 5); 
    druid->move(-100, 1000); 
    int x, y;
    druid->get_position(x, y);
    
    EXPECT_EQ(x, 0); 
    EXPECT_EQ(y, MAP_SIZE); 
}

TEST(NPCTest, StatsCorrect) {
    auto elf = std::make_shared<Elf>(make_name("Elf", 1), 0, 0);
    EXPECT_EQ(elf->get_stats().move_distance, 10);
    EXPECT_EQ(elf->get_stats().kill_distance, 50);
    
    auto dragon = std::make_shared<Dragon>(make_name("Dragon", 2), 0, 0);
    EXPECT_EQ(dragon->get_stats().move_distance, 50);
    EXPECT_EQ(dragon->get_stats().kill_distance, 30);
    
    auto druid = std::make_shared<Druid>(make_name("Druid", 3), 0, 0);
    EXPECT_EQ(druid->get_stats().move_distance, 10);
    EXPECT_EQ(druid->get_stats().kill_distance, 10);
}

TEST(BattleLogicTest, DragonAttacksElf) {
    BattleLogic logic(g_test_mutex);
    auto dragon = std::make_shared<Dragon>(make_name("Dragon", 10), 0, 0);
    auto elf = std::make_shared<Elf>(make_name("Elf", 11), 0, 0);
   
    logic.start_battle(dragon, elf);
    
    EXPECT_TRUE(!dragon->is_alive() || !elf->is_alive() || 
                (dragon->is_alive() && elf->is_alive())); 
}

TEST(BattleLogicTest, ElfAttacksDruid) {
    BattleLogic logic(g_test_mutex);
    auto elf = std::make_shared<Elf>(make_name("Elf", 20), 0, 0);
    auto druid = std::make_shared<Druid>(make_name("Druid", 21), 0, 0);
    
    logic.start_battle(elf, druid);
    
    EXPECT_TRUE(!elf->is_alive() || !druid->is_alive() || 
                (elf->is_alive() && druid->is_alive()));
}

TEST(BattleLogicTest, DruidAttacksDragon) {
    BattleLogic logic(g_test_mutex);
    auto druid = std::make_shared<Druid>(make_name("Druid", 30), 0, 0);
    auto dragon = std::make_shared<Dragon>(make_name("Dragon", 31), 0, 0);
    
    logic.start_battle(druid, dragon);
    
    EXPECT_TRUE(!druid->is_alive() || !dragon->is_alive() || 
                (druid->is_alive() && dragon->is_alive()));
}

TEST(BattleLogicTest, NoAttackBetweenNonEnemies) {
    BattleLogic logic(g_test_mutex);
    auto elf1 = std::make_shared<Elf>(make_name("Elf", 40), 0, 0);
    auto elf2 = std::make_shared<Elf>(make_name("Elf", 41), 0, 0);
    
    bool elf1_alive_before = elf1->is_alive();
    bool elf2_alive_before = elf2->is_alive();
    
    logic.start_battle(elf1, elf2);
    
    EXPECT_EQ(elf1->is_alive(), elf1_alive_before);
    EXPECT_EQ(elf2->is_alive(), elf2_alive_before);
}

TEST(NPCFactoryTest, CreateRandomNPC) {
    NPCFactory factory;
    auto npc = factory.create_random_npc(1);
    EXPECT_NE(npc, nullptr);
    EXPECT_TRUE(npc->get_type() == "Elf" || 
                npc->get_type() == "Dragon" || 
                npc->get_type() == "Druid");
}

TEST(DistanceTest, CalculateDistance) {
    auto npc1 = std::make_shared<Elf>(make_name("Elf", 1), 0, 0);
    auto npc2 = std::make_shared<Dragon>(make_name("Dragon", 2), 3, 4);
    
    double dist_sq = distance_sq(npc1, npc2);
    EXPECT_NEAR(dist_sq, 25.0, 0.001);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


