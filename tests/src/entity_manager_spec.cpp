//
// Created by gilmar on 12/21/21.
//
#include "gtest/gtest.h"
#include "ecs_settings.hpp"

using EntityManager = ecs::EntityManager<Settings>;

class EntityManagerSpec : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        manager = new EntityManager(10000);
    }

    virtual void TearDown() {
        delete manager;
    }

    EntityManager * manager;
};

TEST_F(EntityManagerSpec, SignatureHandleShouldMoveTheLastSignatureAndReset){
    for (int i = 0; i < 1000; i++)
    {
        auto entity = manager->create_entity();

        manager->add_component<TransformComponent>(entity);
    }

    auto& last_signature_ref = manager->get_signature(manager->get_next_entity()-1);
    auto last_signature = last_signature_ref;

    manager->destroy_entity(100);

    ASSERT_EQ(manager->get_signature(100), last_signature);
    ASSERT_EQ(last_signature_ref, EntityManager::Bitset{"000"});
}


TEST_F(EntityManagerSpec, SignatureHandleShouldOnlyResetSignatureWhenTheEntityIsEqualsOrGreaterTheLastEntity){
    for (int i = 0; i < 100; i++)
    {
        auto entity = manager->create_entity();

        manager->add_component<TransformComponent>(entity);
    }

    ecs::EntityID last_entity = manager->get_next_entity()-1;
    ecs::EntityID greater_than_last_entity = 200;

    manager->destroy_entity(last_entity);
    manager->destroy_entity(greater_than_last_entity);

    ASSERT_EQ(manager->get_signature(last_entity), EntityManager::Bitset{"000"});
    ASSERT_EQ(manager->get_signature(greater_than_last_entity), EntityManager::Bitset{"000"});
}