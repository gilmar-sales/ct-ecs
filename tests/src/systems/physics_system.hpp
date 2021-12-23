//
// Created by gilmar on 12/21/21.
//

#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

#include <iostream>
#include <ecs/ecs.hpp>

#include "../components/transform_component.hpp"
#include "../components/rigid_body_component.hpp"

class PhysicsSystem : public ecs::BaseSystem<PhysicsSystem> {
public:
    using Signature = std::tuple<RigidBodyComponent, TransformComponent>;

    template<typename T>
    void update(T &manager) {
        for (auto entity: m_registered_entities) {
            //std::cout << "[phys]: updating entity " << entity << "\n";
        }
    }
};

#endif //PHYSICS_SYSTEM_HPP
