#include <iostream>

#include "base_system.hpp"

#include "../components/transform_component.hpp"

namespace ecs{
    class PhysicsSystem : public BaseSystem<PhysicsSystem>
    {
    private:
        
    public:
        PhysicsSystem(/* args */) {};
        ~PhysicsSystem() = default;

        template<typename T>
        void update(T& comps, float delta_time)
        {
            for(EntityID entity : m_registered_entities)
            {
                TransformComponent& transform = comps.template get_component<TransformComponent>(entity);

                transform.pos_x += 1;
                transform.pos_y += 1;
                transform.pos_z += 1;

                std::cout << "phys process entity: " << entity << std::endl;
            }
        }
    };
    
    
}