#pragma once
#include <iostream>
#include <tuple>

#include <ecs/ecs.hpp>

#include "../core/time.hpp"
#include "../core/input.hpp"

#include "../components/transform_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../tags/tags.hpp"

namespace ecs{

    class PlayerMoveSystem : public BaseSystem<PlayerMoveSystem>
    {
    public:
        using Signature = std::tuple<ecs::TransformComponent, ecs::RigidBodyComponent, ecs::PlayerTag>;

        PlayerMoveSystem() = default;
        ~PlayerMoveSystem() = default;

        template<typename T>
        void update(T& comps)
        {
            for(EntityID entity : m_registered_entities)
            {
                TransformComponent& transform = comps.template get_component<TransformComponent>(entity);
                RigidBodyComponent& rigidbody = comps.template get_component<RigidBodyComponent>(entity);

                if (Input::IsKeyPressed(Key::W)) {
                    glm::vec4 front = {0,1,0,0};
                    glm:: mat4 rotation = {
                        {1,0,0,0},
                        {0,1,0,0},
                        {0,0,1,0},
                        {0,0,0,1}
                    };
                    rotation = glm::rotate(rotation, glm::radians(transform.rotation.z), {0, 0, 1});
                    front = front * rotation;

                    rigidbody.velocity += glm::normalize(glm::vec3(-front.x, front.y, front.z)) * 300.f * Time::delta_time;
                    // transform.position += glm::normalize(glm::vec3(-front.x, front.y, front.z)) * 60.f * Time::delta_time;
                }
                
                if (Input::IsKeyPressed(Key::A)) {
                    transform.rotation.z += 90 * Time::delta_time;
                } else if (Input::IsKeyPressed(Key::D)) {
                    transform.rotation.z -= 90 * Time::delta_time;
                }
            }
        }
    };
    
}
