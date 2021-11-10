#include <iostream>
#include <tuple>

#include <ecs/ecs.hpp>

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

                transform.pos_x += 1;
                transform.pos_y += 1;
                transform.pos_z += 1;

                // std::cout << "phys process entity: " << entity << std::endl;
                // std::cout << "position: " << transform.pos_x << ", " << transform.pos_y << ", " << transform.pos_z << std::endl;
            }
        }
    };
    
}
