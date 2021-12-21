//
// Created by gilmar on 12/21/21.
//

#ifndef CT_ECS_PLAYER_MOVEMENT_SYSTEM_HPP
#define CT_ECS_PLAYER_MOVEMENT_SYSTEM_HPP

#include <iostream>
#include <ecs/ecs.hpp>

#include "../components/transform_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../tags/player_tag.hpp"

class PlayerMovementSystem : public ecs::BaseSystem<PlayerMovementSystem>
{
public:
    using Signature = std::tuple<RigidBodyComponent, TransformComponent, PlayerTag>;

    template<typename T>
    void update(T& manager)
    {
        for (auto entity : m_registered_entities)
        {
        }
    }
};

#endif //CT_ECS_PLAYER_MOVEMENT_SYSTEM_HPP
