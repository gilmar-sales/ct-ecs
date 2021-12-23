#ifndef SPACE_ECS_PHYSICS_SYSTEM_HPP
#define SPACE_ECS_PHYSICS_SYSTEM_HPP

#include <iostream>
#include <tuple>

#include <ecs/ecs.hpp>

#include "../core/time.hpp"
#include "../components/transform_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../tags/tags.hpp"

class Application;

namespace ecs {
    class PhysicsSystem : public BaseSystem<PhysicsSystem> {
    public:
        using Signature = std::tuple<ecs::TransformComponent, ecs::RigidBodyComponent>;

        PhysicsSystem() = default;

        ~PhysicsSystem() = default;

        template<typename T>
        void update(T &manager) {
            for (int i = 0; i < m_registered_entities.size(); i++) {
                auto entity = m_registered_entities[i];
                TransformComponent &transform = manager.template get_component<TransformComponent>(entity);
                RigidBodyComponent &rigidbody = manager.template get_component<RigidBodyComponent>(entity);

                transform.position += rigidbody.velocity * Time::delta_time;

                rigidbody.velocity /= 1 + rigidbody.mass * Time::delta_time;

                if (manager.template has_tag<ecs::EnemyTag>(entity)) {
                    auto radius = transform.scale.x;

                    if (transform.position.x > 400 - radius) {
                        rigidbody.velocity.x *= -1;
                        transform.position.x = 400 - radius;
                    } else if (transform.position.x < -400 + radius) {
                        rigidbody.velocity.x *= -1;
                        transform.position.x = -400 + radius;
                    }

                    if (transform.position.y > 300 - radius) {
                        rigidbody.velocity.y *= -1;
                        transform.position.y = 300 - radius;
                    } else if (transform.position.y < -300 + radius) {
                        rigidbody.velocity.y *= -1;
                        transform.position.y = -300 + radius;
                    }
                } else if (manager.template has_tag<ecs::PlayerTag>(entity)) {
                    if (transform.position.x > 400) {
                        transform.position.x = -400;
                    } else if (transform.position.x < -400) {
                        transform.position.x = 400;
                    }

                    if (transform.position.y > 300) {
                        transform.position.y = -300;
                    } else if (transform.position.y < -300) {
                        transform.position.y = 300;
                    }
                }
            }
        }
    };

} // namespace ecs

#endif // SPACE_ECS_PHYSICS_SYSTEM_HPP
