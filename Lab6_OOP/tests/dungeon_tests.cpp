#include "gtest/gtest.h"
#include "../include/npc.h"
#include "../include/npc_factory.h"
#include "../include/battle_visitor.h"
#include "../include/dungeon_editor.h"
#include "../include/observer.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

class MockObserver : public Observer {
public:
    std::vector<std::string> events;
    void update(const std::string& event) override {
        events.push_back(event);
    }
};

TEST(NPCTest, DistanceCalculation) {
    auto npc1 = std::make_shared<Elf>("E1", 0, 0);
    auto npc2 = std::make_shared<Dragon>("D1", 3, 4); 
    auto npc3 = std::make_shared<Druid>("Dr1", 10, 10);
    
    EXPECT_NEAR(NPC::distance(npc1, npc2), 5.0, 0.001);
    EXPECT_NEAR(NPC::distance(npc1, npc3), 14.142135, 0.001);
    EXPECT_NEAR(NPC::distance(npc1, npc1), 0.0, 0.001);
}

TEST(NPCFactoryTest, CreateValidNPC) {
    NPCFactory factory;
    auto elf = factory.create_npc("Elf", "Legolas", 50, 50);
    EXPECT_NE(elf, nullptr);
    EXPECT_EQ(elf->get_type(), "Elf");
    EXPECT_EQ(elf->get_name(), "Legolas");
    EXPECT_EQ(elf->get_x(), 50);
    EXPECT_EQ(elf->get_y(), 50);
    EXPECT_TRUE(elf->is_alive());
}

TEST(NPCFactoryTest, CreateDragon) {
    NPCFactory factory;
    auto dragon = factory.create_npc("Dragon", "Smaug", 100, 100);
    EXPECT_NE(dragon, nullptr);
    EXPECT_EQ(dragon->get_type(), "Dragon");
    EXPECT_EQ(dragon->get_name(), "Smaug");
}

TEST(NPCFactoryTest, CreateDruid) {
    NPCFactory factory;
    auto druid = factory.create_npc("Druid", "Malfurion", 200, 200);
    EXPECT_NE(druid, nullptr);
    EXPECT_EQ(druid->get_type(), "Druid");
    EXPECT_EQ(druid->get_name(), "Malfurion");
}

TEST(NPCFactoryTest, CreateInvalidType) {
    NPCFactory factory;
    auto unknown = factory.create_npc("Goblin", "Gobby", 10, 10);
    EXPECT_EQ(unknown, nullptr);
}

TEST(NPCFactoryTest, CoordinateValidation) {
    NPCFactory factory;
    EXPECT_NE(factory.create_npc("Elf", "Max", 500, 500), nullptr);
    EXPECT_NE(factory.create_npc("Dragon", "Min", 0, 0), nullptr);
    
    EXPECT_EQ(factory.create_npc("Elf", "OutX", 501, 100), nullptr);
    EXPECT_EQ(factory.create_npc("Dragon", "OutY", 100, -1), nullptr);
}

TEST(NPCFactoryTest, CreateFromFileString) {
    NPCFactory factory;
    std::string file_string = "Elf|Legolas|150|200";
    auto elf = factory.create_npc_from_file_string(file_string);
    
    EXPECT_NE(elf, nullptr);
    EXPECT_EQ(elf->get_type(), "Elf");
    EXPECT_EQ(elf->get_name(), "Legolas");
    EXPECT_EQ(elf->get_x(), 150);
    EXPECT_EQ(elf->get_y(), 200);
}

TEST(NPCFactoryTest, CreateFromFileInvalidFormat) {
    NPCFactory factory;
    EXPECT_EQ(factory.create_npc_from_file_string("Elf|Wrong|100"), nullptr);
    EXPECT_EQ(factory.create_npc_from_file_string("Goblin|Gobby|10|10"), nullptr);
}

class BattleTest : public ::testing::Test {
protected:
    BattleVisitor visitor;
    std::shared_ptr<MockObserver> mock_obs = std::make_shared<MockObserver>();
    
    void SetUp() override {
        visitor.add_observer(mock_obs);
    }
    
    template <typename T>
    std::shared_ptr<T> create_npc(const std::string& name, int x, int y) {
        return std::make_shared<T>(name, x, y);
    }
};

// Правила боя:
// Дракон нападает на эльфов -> Дракон убивает Эльфа
// Эльф нападает на друида -> Эльф убивает Друида
// Друид нападает на дракона -> Друид убивает Дракона

TEST_F(BattleTest, DragonVsElf_DragonWins) {
    auto dragon = create_npc<Dragon>("D", 10, 10);
    auto elf = create_npc<Elf>("E", 10, 10);
    dragon->accept(visitor, elf);
    
    EXPECT_FALSE(elf->is_alive());
    EXPECT_TRUE(dragon->is_alive());
    
    ASSERT_EQ(mock_obs->events.size(), 1);
    EXPECT_EQ(mock_obs->events[0], "Dragon (D) killed Elf (E)");
}

TEST_F(BattleTest, ElfVsDruid_ElfWins) {
    auto elf = create_npc<Elf>("E", 10, 10);
    auto druid = create_npc<Druid>("Dr", 10, 10);
    elf->accept(visitor, druid);
    
    EXPECT_TRUE(elf->is_alive());
    EXPECT_FALSE(druid->is_alive());
    
    ASSERT_EQ(mock_obs->events.size(), 1);
    EXPECT_EQ(mock_obs->events[0], "Elf (E) killed Druid (Dr)");
}

TEST_F(BattleTest, DruidVsDragon_DruidWins) {
    auto druid = create_npc<Druid>("Dr", 10, 10);
    auto dragon = create_npc<Dragon>("D", 10, 10);
    druid->accept(visitor, dragon);
    
    EXPECT_TRUE(druid->is_alive());
    EXPECT_FALSE(dragon->is_alive());
    
    ASSERT_EQ(mock_obs->events.size(), 1);
    EXPECT_EQ(mock_obs->events[0], "Druid (Dr) killed Dragon (D)");
}

TEST_F(BattleTest, DragonVsDruid_NoFight) {
    auto dragon = create_npc<Dragon>("D", 10, 10);
    auto druid = create_npc<Druid>("Dr", 10, 10);
    dragon->accept(visitor, druid);
    
    // Дракон не нападает на друида, оба должны остаться живыми
    EXPECT_TRUE(dragon->is_alive());
    EXPECT_TRUE(druid->is_alive());
    EXPECT_EQ(mock_obs->events.size(), 0);
}

TEST_F(BattleTest, ElfVsDragon_NoFight) {
    auto elf = create_npc<Elf>("E", 10, 10);
    auto dragon = create_npc<Dragon>("D", 10, 10);
    elf->accept(visitor, dragon);
    
    // Эльф не нападает на дракона, оба должны остаться живыми
    EXPECT_TRUE(elf->is_alive());
    EXPECT_TRUE(dragon->is_alive());
    EXPECT_EQ(mock_obs->events.size(), 0);
}

TEST_F(BattleTest, DruidVsElf_NoFight) {
    auto druid = create_npc<Druid>("Dr", 10, 10);
    auto elf = create_npc<Elf>("E", 10, 10);
    druid->accept(visitor, elf);
    
    // Друид не нападает на эльфа, оба должны остаться живыми
    EXPECT_TRUE(druid->is_alive());
    EXPECT_TRUE(elf->is_alive());
    EXPECT_EQ(mock_obs->events.size(), 0);
}

TEST(DungeonEditorTest, AddNPC) {
    DungeonEditor editor;
    EXPECT_TRUE(editor.add_npc("Elf", "Legolas", 50, 50));
    EXPECT_TRUE(editor.add_npc("Dragon", "Smaug", 100, 100));
    EXPECT_TRUE(editor.add_npc("Druid", "Malfurion", 200, 200));
}

TEST(DungeonEditorTest, AddDuplicateName) {
    DungeonEditor editor;
    EXPECT_TRUE(editor.add_npc("Elf", "Legolas", 50, 50));
    EXPECT_FALSE(editor.add_npc("Dragon", "Legolas", 100, 100));
}

TEST(DungeonEditorTest, SaveAndLoad) {
    DungeonEditor editor;
    editor.add_npc("Elf", "Legolas", 50, 50);
    editor.add_npc("Dragon", "Smaug", 100, 100);
    editor.add_npc("Druid", "Malfurion", 200, 200);
    
    std::string filename = "test_save.txt";
    EXPECT_TRUE(editor.save(filename));
    
    DungeonEditor editor2;
    EXPECT_TRUE(editor2.load(filename));
    
    // Clean up
    std::remove(filename.c_str());
}

TEST(DungeonEditorTest, BattleWithDistance) {
    DungeonEditor editor;
    editor.add_npc("Dragon", "D1", 0, 0);
    editor.add_npc("Elf", "E1", 0, 0);  // Same position, distance = 0
    editor.add_npc("Druid", "Dr1", 100, 100);  // Far away
    
    editor.run_battle(10.0);
    
    // Dragon should kill Elf (distance 0 <= 10)
    // Druid is too far, no fight
}


