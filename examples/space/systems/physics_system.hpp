#pragma once
#include <iostream>
#include <tuple>

#include <ecs/ecs.hpp>

#include "../core/time.hpp"
#include "../components/transform_component.hpp"

namespace ecs{

    class PhysicsSystem : public BaseSystem<PhysicsSystem>
    {
    public:
        using Signature = std::tuple<ecs::TransformComponent>;

        PhysicsSystem() = default;
        ~PhysicsSystem() = default;

        template<typename T>
        void update(T& comps)
        {
            for(EntityID entity : m_registered_entities)
            {
                TransformComponent& transform = comps.template get_component<TransformComponent>(entity);

                //transform.position.x += 1 * Time::delta_time;
                transform.position.y += 0.0001f * Time::delta_time;
                //transform.position.z += 1;

                // std::cout << "phys process entity: " << entity << std::endl;
                // std::cout << "position: " << transform.pos_x << ", " << transform.pos_y << ", " << transform.pos_z << std::endl;
            }
        }
    };
    
}
