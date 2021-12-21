//
// Created by gilmar on 12/21/21.
//

#ifndef CT_ECS_ENEMY_MOVEMENT_SYSTEM_HPP
#define CT_ECS_ENEMY_MOVEMENT_SYSTEM_HPP

#include <iostream>
#include <ecs/ecs.hpp>

#include "../components/transform_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../tags/enemy_tag.hpp"

class EnemyMovementSystem : public ecs::BaseSystem<EnemyMovementSystem>
{
public:
    using Signature = std::tuple<RigidBodyComponent, TransformComponent, EnemyTag>;

    template<typename T>
    void update(T& manager)
    {
        for (auto entity : m_registered_entities)
        {
        }
    }
};

#endif //CT_ECS_ENEMY_MOVEMENT_SYSTEM_HPP
