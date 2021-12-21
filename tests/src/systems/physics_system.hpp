//
// Created by gilmar on 12/21/21.
//

#ifndef CT_ECS_PHYSICS_SYSTEM_HPP
#define CT_ECS_PHYSICS_SYSTEM_HPP

#include <iostream>
#include <ecs/ecs.hpp>

#include "../components/transform_component.hpp"

class PhysicsSystem : public ecs::BaseSystem<PhysicsSystem>
{
public:
    using Signature = std::tuple<TransformComponent>;

    template<typename T>
    void update(T& manager)
    {
        for (auto entity : m_registered_entities)
        {
            std::cout << "[phys]: updating entity " << entity << "\n";
        }
    }
};

#endif //CT_ECS_PHYSICS_SYSTEM_HPP
