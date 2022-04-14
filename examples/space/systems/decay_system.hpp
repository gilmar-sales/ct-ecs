#ifndef SPACE_ECS_DECAY_SYSTEM_HPP
#define SPACE_ECS_DECAY_SYSTEM_HPP

#include <iostream>

#include <ecs/ecs.hpp>

#include "../core/time.hpp"

#include "../components/decay_component.hpp"
#include "../tags/tags.hpp"

class Application;

namespace ecs {

    class DecaySystem : public BaseSystem<DecaySystem> {
    public:
        using Signature = std::tuple<ecs::DecayComponent, ecs::BulletTag>;

        DecaySystem() = default;

        ~DecaySystem() = default;

        template<typename Settings>
        void update(Manager<Settings>* manager) {
            for (int i = 0; i < m_registered_entities.size(); i++) {
                auto entity = m_registered_entities[i];
                DecayComponent &decay = manager->template get_component<DecayComponent>(entity);
                decay.current += Time::delta_time;

                if (decay.current > decay.max_time) {
                    decay.current = 0.f;
                    decay.max_time = 0.f;
                    manager->destroy_entity(entity);
                }
            }
        }
    };

} // namespace ecs

#endif // SPACE_ECS_DECAY_SYSTEM_HPP
