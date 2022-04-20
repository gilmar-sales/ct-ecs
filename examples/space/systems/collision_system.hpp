#ifndef SPACE_ECS_COLLISION_SYSTEM_HPP
#define SPACE_ECS_COLLISION_SYSTEM_HPP

#include <iostream>
#include <tuple>

#include <ecs/ecs.hpp>

#include "../core/time.hpp"
#include "../components/transform_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../components/circle_collider_component.hpp"
#include "../components/player_component.hpp"
#include "../tags/tags.hpp"

#include "../utils/quadtree.hpp"

class Application;

namespace ecs {
    class CollisionSystem : public BaseSystem<CollisionSystem> {
    public:
        using Signature = std::tuple<ecs::TransformComponent, ecs::RigidBodyComponent, ecs::CircleColliderComponent>;

        CollisionSystem() = default;

        ~CollisionSystem() = default;

        template<typename Settings>
        void update(Manager<Settings>* manager) {
            QuadTree quadtree = QuadTree(glm::vec2(0, 0), 400.f, 4);

            for (int i = 0; i < m_registered_entities.size(); i++) {
                auto entity = m_registered_entities[i];
                TransformComponent &transform = manager->template get_component<TransformComponent>(entity);
                CircleColliderComponent &collider = manager->template get_component<CircleColliderComponent>(entity);
                quadtree.insert({entity, glm::vec2(transform.position.x, transform.position.y), collider.radius});
            }

            for (EntityID entity : m_registered_entities) {
                auto &transform = manager->template get_component<TransformComponent>(entity);
                auto &rigidbody = manager->template get_component<RigidBodyComponent>(entity);
                auto &collider = manager->template get_component<CircleColliderComponent>(entity);

                Entity ent = {entity, glm::vec2(transform.position.x, transform.position.y), collider.radius};
                std::vector<Entity> collisions = std::vector<Entity>();
                quadtree.query(ent, &collisions);

                if (manager->template has_tag<ecs::BulletTag>(entity)) {
                    for (auto collision: collisions) {
                        if (manager->template has_tag<ecs::EnemyTag>(collision.id)) {
                            manager->destroy_entity(entity);

                            BulletComponent &bullet_comp = manager->template get_component<BulletComponent>(entity);
                            manager->template get_component<PlayerComponent>(bullet_comp.owner).score += 1;

                            float new_radius = collision.radius / 2.f;
                            float new_scale = new_radius / 32.f;

                            if (new_radius > 10) {
                                TransformComponent &meteor_transform = manager->template get_component<TransformComponent>(
                                        collision.id);
                                CircleColliderComponent &meteor_collider = manager->template get_component<CircleColliderComponent>(
                                        collision.id);

                                meteor_transform.scale = {new_scale, new_scale, new_scale};
                                meteor_collider.radius = new_radius;
                            } else {
                                manager->destroy_entity(collision.id);
                            }
                        }
                    }
                } else if (manager->template has_tag<ecs::PlayerTag>(entity)) {
                    for (auto collision: collisions) {
                        if (manager->template has_tag<ecs::EnemyTag>(collision.id)) {
                            manager->destroy_entity(collision.id);

                            PlayerComponent &life = manager->template get_component<PlayerComponent>(entity);
                            life.lifes -= 1;
                            break;
                        }
                    }
                }
            }
        }
    };

} // namespace ecs

#endif // SPACE_ECS_COLLISION_SYSTEM_HPP
