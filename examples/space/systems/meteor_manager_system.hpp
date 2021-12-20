#pragma once
#include <iostream>
#include <tuple>

#include <ecs/ecs.hpp>

#include "../core/time.hpp"

#include "../components/transform_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../tags/tags.hpp"

namespace ecs
{

    class MeteorManagerSystem : public BaseSystem<MeteorManagerSystem>
    {
    public:
        using Signature = std::tuple<ecs::MeteorManagerTag>;

        MeteorManagerSystem() = default;
        ~MeteorManagerSystem() = default;

        template <typename T>
        void update(T &comps)
        {
            for (int i = 0; i < m_registered_entities.size(); i++)
            {
                auto entity = m_registered_entities[i];
            }
        }
    };

}
