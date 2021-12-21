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
                            manager.destroy_entity(entity);
                            
                            float new_radius = collision.radius / 2.f;
                            if (new_radius > 10) {
                                    std::random_device rd; // obtain a random number from hardware
                                    std::mt19937 gen(rd()); // seed the generator
                                    std::uniform_int_distribution<> distrPos(-collision.radius*2.f, collision.radius*2.f); // define the range
                                    std::uniform_int_distribution<> distrScale(10, 50); // define the rangev
                                    std::uniform_int_distribution<> distrAngle(0, 360); // define the rangev
                                for (int i = 0; i < 4; i++)
                                {
                                    auto fragment = manager.create_entity();
                                    manager.add_tag<ecs::EnemyTag>(fragment);

                                    TransformComponent &fragment_transform = manager. template add_component<TransformComponent>(fragment);
                                    RigidBodyComponent &fragment_rigidbody = manager. template add_component<RigidBodyComponent>(fragment);
                                    MeshComponent &fragment_mesh = manager. template add_component<MeshComponent>(fragment);
                                    CircleColliderComponent &fragment_collider = manager. template add_component<CircleColliderComponent>(fragment);

                                    
                                    float x = distrPos(gen);
                                    float y = distrPos(gen);

                                    float angle = distrAngle(gen);

                                    float speed = distrScale(gen);
                                    float size = distrScale(gen);

                                    fragment_transform.position = glm::vec3(collision.position.x + x, collision.position.y + y, 0.f);
                                    fragment_transform.scale = {new_radius, new_radius, new_radius};
                                    fragment_transform.rotation = {0.f, 0.f, 0.f};

                                    fragment_rigidbody.velocity = glm::normalize(fragment_transform.position) * speed;
                                    fragment_rigidbody.mass = 0;
                                    fragment_mesh.VAO = MeshAsset::initCircleMesh();
                                    fragment_collider.radius = new_radius;
                                }
                            }

                            manager.destroy_entity(collision.id);
                        }
                    }
                }
            }
        }
    };

}
