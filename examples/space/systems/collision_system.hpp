#pragma once
#include <iostream>
#include <tuple>

#include <ecs/ecs.hpp>

#include "../core/time.hpp"
#include "../components/transform_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../components/circle_collider_component.hpp"
#include "../tags/tags.hpp"

#include "../utils/quadtree.hpp"

class Application;

namespace ecs
{
    class CollisionSystem : public BaseSystem<CollisionSystem>
    {
    public:
        using Signature = std::tuple<ecs::TransformComponent, ecs::RigidBodyComponent, ecs::CircleColliderComponent>;

        CollisionSystem() = default;
        ~CollisionSystem() = default;

        template <typename T>
        void update(T &manager)
        {
            QuadTree quadtree = QuadTree(glm::vec2(0,0), 400.f, 4);
            
            for (int i = 0; i < m_registered_entities.size(); i++)
            {
                auto entity = m_registered_entities[i];
                TransformComponent &transform = manager.template get_component<TransformComponent>(entity);
                CircleColliderComponent &collider = manager.template get_component<CircleColliderComponent>(entity);
                quadtree.insert({entity, glm::vec2(transform.position.x, transform.position.y), collider.radius});
            }

            for (int i = 0; i < m_registered_entities.size(); i++)
            {
                auto entity = m_registered_entities[i];
                TransformComponent &transform = manager.template get_component<TransformComponent>(entity);
                RigidBodyComponent &rigidbody = manager.template get_component<RigidBodyComponent>(entity);
                CircleColliderComponent &collider = manager.template get_component<CircleColliderComponent>(entity);
                
                Entity ent = {entity, glm::vec2(transform.position.x, transform.position.y), collider.radius};
                std::vector<Entity> collisions = std::vector<Entity>();
                quadtree.query(ent, &collisions);

                if (manager.template has_tag<ecs::BulletTag>(entity)) 
                {
                    for (auto collision : collisions) {
                        if (manager.template has_tag<ecs::EnemyTag>(collision.id)) {
                            manager.template destroy_entity(entity);
                            manager.template destroy_entity(collision.id);
                        }
                    }
                }
            }
        }
    };

}
