//
// Created by gilma on 22/12/2021.
//

#ifndef SPACE_ECS_PLAYER_SYSTEM_HPP
#define SPACE_ECS_PLAYER_SYSTEM_HPP

#include <iostream>
#include <tuple>

#include <ecs/ecs.hpp>

#include "../core/time.hpp"
#include "../core/input.hpp"

#include "../components/player_component.hpp"
#include "../components/transform_component.hpp"
#include "../tags/tags.hpp"

namespace ecs {
    class PlayerSystem : public BaseSystem<PlayerSystem> {
    public:
        using Signature = std::tuple<ecs::PlayerTag, ecs::PlayerComponent, ecs::TransformComponent>;

        PlayerSystem() = default;

        ~PlayerSystem() = default;

        template<typename T>
        void update(T &comps) {
            for (int i = 0; i < m_registered_entities.size(); i++) {
                auto entity = m_registered_entities[i];
                TransformComponent &transform = comps.template get_component<TransformComponent>(entity);
                PlayerComponent &player = comps.template get_component<PlayerComponent>(entity);

                if (player.lifes <= 0) {
                    transform.position = {0.f, 0.f, 0.f};
                    player.lifes = 4;
                    player.score = 0;
                }
            }
        }
    };

}

#endif //SPACE_ECS_PLAYER_SYSTEM_HPP
