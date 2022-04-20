#ifndef SPACE_ECS_SHOOT_SYSTEM_HPP
#define SPACE_ECS_SHOOT_SYSTEM_HPP

#include <iostream>

#include <ecs/ecs.hpp>

#include "../core/time.hpp"
#include "../core/input.hpp"
#include "../core/texture_manager.hpp"

#include "../components/transform_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../components/decay_component.hpp"
#include "../components/bullet_component.hpp"
#include "../components/laser_gun_component.hpp"
#include "../tags/tags.hpp"

namespace ecs {

    class ShootSystem : public BaseSystem<ShootSystem> {
    public:
        using Signature = std::tuple<ecs::TransformComponent, ecs::RigidBodyComponent, ecs::LaserGunComponent>;

        ShootSystem() = default;

        ~ShootSystem() = default;

        template<typename Settings>
        void update(Manager<Settings>* manager) {
            for (int i = 0; i < m_registered_entities.size(); i++) {
                auto entity = m_registered_entities[i];
                auto &transform = manager->template get_component<TransformComponent>(entity);
                auto &rigidbody = manager->template get_component<RigidBodyComponent>(entity);
                auto &gun = manager->template get_component<LaserGunComponent>(entity);

                if (gun.time > 1.0f) {
                    gun.time = 0.0f;
                    gun.current_shots = 0;
                }

                gun.time += Time::delta_time;

                if (Input::GetKeyDown(Key::Space) && gun.current_shots < gun.max_shots_per_second) {
                    glm::vec3 forward = transform.get_forward_direction();
                    glm::vec3 right = transform.get_right_direction();

                    auto left_bullet = create_bullet(manager, entity);

                    auto &left_bullet_transform = manager->template add_component<TransformComponent>(left_bullet);
                    left_bullet_transform.position = transform.position + glm::normalize(forward  - right) * 26.f;

                    auto right_bullet = create_bullet(manager, entity);
                    auto &right_bullet_transform = manager->template add_component<TransformComponent>(right_bullet);
                    right_bullet_transform.position = transform.position + glm::normalize(forward  + right) * 26.f;

                    gun.current_shots += 1;
                }
            }
        }

        template<typename Settings>
        EntityID create_bullet(Manager<Settings>* manager, EntityID owner) {
            auto &transform = manager->template get_component<TransformComponent>(owner);

            auto bullet = manager->create_entity();

            auto &bullet_transform = manager->template add_component<TransformComponent>(bullet);
            auto &bullet_rigidbody = manager->template add_component<RigidBodyComponent>(bullet);
            auto &bullet_sprite = manager->template add_component<SpriteComponent>(bullet);
            auto &bullet_decay = manager->template add_component<DecayComponent>(bullet);
            auto &bullet_collider = manager->template add_component<CircleColliderComponent>(bullet);
            auto &bullet_comp = manager->template add_component<BulletComponent>(bullet);

            manager->template add_tag<BulletTag>(bullet);
            glm::vec3 forward = transform.get_forward_direction();

            bullet_transform.rotation = transform.rotation;
            bullet_transform.scale = {1.f, 1.f, 1.f};
            bullet_rigidbody.velocity = forward * 500.f;
            bullet_rigidbody.mass = 0;

            bullet_sprite.textures[0] = TextureManager::get()->get_texture_index("resources/shoot.png");
            bullet_sprite.textures_count = 1;

            bullet_decay.max_time = 0.8f;
            bullet_decay.current = 0.f;
            bullet_collider.radius = 5;
            bullet_comp.owner = owner;

            return bullet;
        }
    };

} // namespace ecs

#endif // SPACE_ECS_SHOOT_SYSTEM_HPP
