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
    for (int i = 0; i < 2; i++)
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