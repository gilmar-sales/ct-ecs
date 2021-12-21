//
// Created by gilmar on 12/21/21.
//
#include "gtest/gtest.h"
#include <ecs/ecs.hpp>

#include "tags/player_tag.hpp"
#include "systems/physics_system.hpp"

using ComponentList = std::tuple<TransformComponent>;
using TagList = std::tuple<PlayerTag>;
using SystemList = std::tuple<PhysicsSystem>;
using Settings = ecs::Settings<ComponentList, TagList, SystemList>;
using ECSManager = ecs::Manager<Settings>;

class EntityManagerSpec : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        manager = new ECSManager();
    }

    virtual void TearDown() {
        delete manager;
    }

    ECSManager * manager;
};

TEST_F(EntityManagerSpec, RegisterSystems){
    auto entity = manager->create_entity();

    manager->add_component(entity, TransformComponent{});

    manager->update();
}