#pragma once
#include <iostream>

#include <ecs/ecs.hpp>

#include "../core/time.hpp"

#include "../components/decay_component.hpp"

class Application;

namespace ecs
{

    class DecaySystem : public BaseSystem<DecaySystem>
    {
    public:
        using Signature = std::tuple<ecs::DecayComponent>;

        DecaySystem() = default;
        ~DecaySystem() = default;

        template <typename T>
        void update(T &manager)
        {
            for (int i = 0; i < m_registered_entities.size(); i++)
            {
                auto entity = m_registered_entities[i];
                DecayComponent &decay = manager.template get_component<DecayComponent>(entity);
                decay.current += Time::delta_time;

                if (decay.current > decay.max_time)
                {
                    decay = {0};
                    manager.template destroy_entity(entity);
                }
            }
        }
    };

}
