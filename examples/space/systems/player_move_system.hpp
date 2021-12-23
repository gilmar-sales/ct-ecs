#ifndef SPACE_ECS_PLAYER_MOVE_SYSTEM_HPP
#define SPACE_ECS_PLAYER_MOVE_SYSTEM_HPP

#include <iostream>
#include <tuple>

#include <ecs/ecs.hpp>

#include "../core/time.hpp"
#include "../core/input.hpp"

#include "../components/transform_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../tags/tags.hpp"

namespace ecs {

    class PlayerMoveSystem : public BaseSystem<PlayerMoveSystem> {
    public:
        using Signature = std::tuple<ecs::TransformComponent, ecs::RigidBodyComponent, ecs::PlayerTag>;

        PlayerMoveSystem() = default;

        ~PlayerMoveSystem() = default;

        template<typename T>
        void update(T &comps) {
            for (int i = 0; i < m_registered_entities.size(); i++) {
                auto entity = m_registered_entities[i];
                TransformComponent &transform = comps.template get_component<TransformComponent>(entity);
                RigidBodyComponent &rigidbody = comps.template get_component<RigidBodyComponent>(entity);

                if (Input::IsKeyPressed(Key::W)) {
                    glm::vec3 forward = transform.get_forward_direction();

                    rigidbody.velocity += forward * 300.f * Time::delta_time;
                }

                if (Input::IsKeyPressed(Key::A)) {
                    transform.rotation.z += 90 * Time::delta_time;
                } else if (Input::IsKeyPressed(Key::D)) {
                    transform.rotation.z -= 90 * Time::delta_time;
                }
            }
        }
    };

} // namespace ecs

#endif // SPACE_ECS_PLAYER_MOVE_SYSTEM_HPP
