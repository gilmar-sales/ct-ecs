//
// Created by gilmar on 12/21/21.
//

#ifndef PLAYER_MOVEMENT_SYSTEM_HPP
#define PLAYER_MOVEMENT_SYSTEM_HPP

#include <iostream>
#include <ecs/ecs.hpp>

#include "../components/transform_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../tags/player_tag.hpp"

class PlayerMovementSystem : public ecs::BaseSystem<PlayerMovementSystem> {
public:
    using Signature = std::tuple<RigidBodyComponent, TransformComponent, PlayerTag>;

    template<typename T>
    void update(T &manager) {
        for (auto entity: m_registered_entities) {
        }
    }
};

#endif //PLAYER_MOVEMENT_SYSTEM_HPP
