#pragma once
#include <iostream>
#include <tuple>

#include <ecs/ecs.hpp>

#include "../core/time.hpp"
#include "../components/transform_component.hpp"
#include "../components/rigid_body_component.hpp"

namespace ecs
{

    class PhysicsSystem : public BaseSystem<PhysicsSystem>
    {
    public:
        using Signature = std::tuple<ecs::TransformComponent, ecs::RigidBodyComponent>;

        PhysicsSystem() = default;
        ~PhysicsSystem() = default;

        template <typename T>
        void update(T &comps)
        {
            for (int i = 0; i < m_registered_entities.size(); i++)
            {
                auto entity = m_registered_entities[i];
                TransformComponent &transform = comps.template get_component<TransformComponent>(entity);
                RigidBodyComponent &rigidbody = comps.template get_component<RigidBodyComponent>(entity);

                transform.position += rigidbody.velocity * Time::delta_time;

                rigidbody.velocity /= 1 + rigidbody.mass * Time::delta_time;

                if (transform.position.x > 400)
                {
                    transform.position.x = -400;
                }
                else if (transform.position.x < -400)
                {
                    transform.position.x = 400;
                }

                if (transform.position.y > 300)
                {
                    transform.position.y = -300;
                }
                else if (transform.position.y < -300)
                {
                    transform.position.y = 300;
                }
            }
        }
    };

}
