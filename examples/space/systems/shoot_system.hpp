#ifndef SPACE_ECS_SHOOT_SYSTEM_HPP
#define SPACE_ECS_SHOOT_SYSTEM_HPP

#include <iostream>

#include <ecs/ecs.hpp>

#include "../core/time.hpp"
#include "../core/input.hpp"
#include "../core/mesh_asset.hpp"

#include "../components/transform_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../components/decay_component.hpp"
#include "../components/bullet_component.hpp"
#include "../tags/tags.hpp"

namespace ecs {

    class ShootSystem : public BaseSystem<ShootSystem> {
    public:
        using Signature = std::tuple<ecs::TransformComponent, ecs::RigidBodyComponent, ecs::PlayerTag>;

        ShootSystem() = default;

        ~ShootSystem() = default;

        template<typename T>
        void update(T &manager) {
            for (int i = 0; i < m_registered_entities.size(); i++) {
                auto entity = m_registered_entities[i];
                TransformComponent &transform = manager.template get_component<TransformComponent>(entity);
                RigidBodyComponent &rigidbody = manager.template get_component<RigidBodyComponent>(entity);

                if (Input::GetKeyDown(Key::Space)) {
                    auto bullet = manager.create_entity();

                    TransformComponent &bullet_transform = manager.template add_component<TransformComponent>(bullet);
                    RigidBodyComponent &bullet_rigidbody = manager.template add_component<RigidBodyComponent>(bullet);
                    MeshComponent &bullet_mesh = manager.template add_component<MeshComponent>(bullet);
                    DecayComponent &bullet_decay = manager.template add_component<DecayComponent>(bullet);
                    CircleColliderComponent &bullet_collider = manager.template add_component<CircleColliderComponent>(
                            bullet);
                    BulletComponent &bullet_comp = manager.template add_component<BulletComponent>(bullet);
                    manager.template add_tag<BulletTag>(bullet);
                    glm::vec3 forward = transform.get_forward_direction();

                    bullet_transform.position = transform.position + forward * 5.f;
                    bullet_transform.scale = {5.f, 5.f, 5.f};
                    bullet_rigidbody.velocity = forward * 500.f;
                    bullet_rigidbody.mass = 0;
                    bullet_mesh.VAO = MeshAsset::get_circle_mesh();
                    bullet_decay.max_time = 0.8f;
                    bullet_decay.current = 0.f;
                    bullet_collider.radius = 5;
                    bullet_comp.owner = entity;
                }
            }
        }
    };

} // namespace ecs

#endif // SPACE_ECS_SHOOT_SYSTEM_HPP
