//
// Created by gilmar on 12/21/21.
//


#include "gtest/gtest.h"
#include "ecs_settings.hpp"

using ECSManager = ecs::Manager<Settings>;

class ECSManagerSpec : public ::testing::Test {
protected:
    virtual void SetUp() {
        manager = new ECSManager();
    }

    virtual void TearDown() {
        delete manager;
    }

    ECSManager *manager;
};

TEST_F(ECSManagerSpec, ManagerInitializeSystemsWithCorrectSignatures) {
    ASSERT_EQ(manager->get_system_signature<PhysicsSystem>(), ECSManager::Bitset{"011"});
    ASSERT_EQ(manager->get_system_signature<EnemyMovementSystem>(), ECSManager::Bitset{"10011"});
    ASSERT_EQ(manager->get_system_signature<PlayerMovementSystem>(), ECSManager::Bitset{"01011"});
}

TEST_F(ECSManagerSpec, SystemsHasRegisteredTheCorrectEntities) {
    ecs::sparse_set<ecs::EntityID> players = {2048};
    ecs::sparse_set<ecs::EntityID> enemies = {2048};

    for (int i = 0; i < 1000; i++) {
        auto player = manager->create_entity();
        players.insert(player);

        manager->add_tag<PlayerTag>(player);

        manager->add_component(player, NameComponent{"Player"});
        manager->add_component(player, TransformComponent{});
        manager->add_component(player, RigidBodyComponent{});
    }

    for (int i = 0; i < 1000; i++) {
        auto enemy = manager->create_entity();
        enemies.insert(enemy);

        manager->add_tag<EnemyTag>(enemy);

        manager->add_component(enemy, NameComponent{"Enemy"});
        manager->add_component(enemy, TransformComponent{});
        manager->add_component(enemy, RigidBodyComponent{});
    }

    for (ecs::EntityID entity = 750; entity < 1250; entity++) {
        if (manager->has_tag<PlayerTag>(entity)) {
            players.remove(entity);
        } else {
            enemies.remove(entity);
        }

        manager->destroy_entity(entity);
    }

    ASSERT_EQ(manager->get_registered_entities<PlayerMovementSystem>().size(), players.size());


    for (ecs::EntityID entity = 375; entity < 750; entity++) {
        if (manager->has_tag<PlayerTag>(entity)) {
            players.remove(entity);
        } else {
            enemies.remove(entity);
        }

        manager->destroy_entity(entity);
    }

    std::cout << "players: \n";
    for (auto player : manager->get_registered_entities<PlayerMovementSystem>())
    {
        std::cout << player << "\n";
        ASSERT_LT(player, 375);
        ASSERT_EQ(std::string(manager->get_component<NameComponent>(player).name), std::string("Player"));
    }

    ASSERT_GT(manager->get_registered_entities<EnemyMovementSystem>().size(), 0);
    ASSERT_EQ(manager->get_registered_entities<EnemyMovementSystem>().size(), enemies.size());

    std::cout << "enemies: \n";
    for (auto enemy : manager->get_registered_entities<EnemyMovementSystem>())
    {
        std::cout << enemy << "\n";
        ASSERT_GE(enemy, 375);
        ASSERT_EQ(std::string(manager->get_component<NameComponent>(enemy).name), std::string("Enemy"));
    }
};
