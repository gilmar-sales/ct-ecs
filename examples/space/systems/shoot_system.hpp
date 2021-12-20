#pragma once
#include <iostream>

#include <ecs/ecs.hpp>

#include "../core/time.hpp"
#include "../core/input.hpp"

#include "../components/transform_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../components/decay_component.hpp"
#include "../tags/tags.hpp"

class Application;

namespace ecs
{

    class ShootSystem : public BaseSystem<ShootSystem>
    {
    public:
        using Signature = std::tuple<ecs::TransformComponent, ecs::RigidBodyComponent, ecs::PlayerTag>;

        ShootSystem() = default;
        ~ShootSystem() = default;

        template <typename T>
        void update(T &comps)
        {
            for (int i = 0; i < m_registered_entities.size(); i++)
            {
                auto entity = m_registered_entities[i];
                TransformComponent &transform = comps.template get_component<TransformComponent>(entity);
                RigidBodyComponent &rigidbody = comps.template get_component<RigidBodyComponent>(entity);

                if (Input::GetKeyDown(Key::Space))
                {
                    auto bullet = Application::get_manager().create_entity();

                    TransformComponent &bullet_transform = Application::get_manager().add_component<TransformComponent>(bullet);
                    RigidBodyComponent &bullet_rigidbody = Application::get_manager().add_component<RigidBodyComponent>(bullet);
                    MeshComponent &bullet_mesh = Application::get_manager().add_component<MeshComponent>(bullet);
                    DecayComponent &bullet_decay = Application::get_manager().add_component<DecayComponent>(bullet);

                    glm::vec4 front = {0, 1, 0, 0};
                    glm::mat4 rotation = {
                        {1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 1}};
                    rotation = glm::rotate(rotation, glm::radians(transform.rotation.z), {0, 0, 1});
                    front = front * rotation;

                    glm::vec3 forward = glm::normalize(glm::vec3(-front.x, front.y, front.z));

                    bullet_transform.position = transform.position + forward * 5.f;
                    bullet_transform.scale = {5};
                    bullet_rigidbody.velocity = forward * 500.f;
                    bullet_rigidbody.mass = 0;
                    bullet_mesh.VAO = Application::initCircleMesh();
                    bullet_decay.max_time = 3.0f;
                    bullet_decay.current = 0.f;
                }
            }
        }
    };

}
