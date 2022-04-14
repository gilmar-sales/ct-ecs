#ifndef CT_ECS_BASE_SYSTEM_HPP
#define CT_ECS_BASE_SYSTEM_HPP

#include "../core/type_defs.hpp"
#include "../core/sparse_set.hpp"

namespace ecs {
    template<typename Derived, typename Subscribers = std::tuple<>>
    class BaseSystem {
    public:
        explicit BaseSystem(unsigned capacity = 1024u) : m_registered_entities(capacity) {

        }

        template<typename Settings>
        void update(Manager<Settings>* manager) {
            static_cast<Derived *>(this)->update(manager);
        }

        template<typename Settings, typename Event>
        void notify(Manager<Settings>* manager, Event event) {
            mp::for_tuple([this, manager, event](auto system){
                auto& receiver = manager->template get_system<decltype(system)>();
                receiver.receive(manager, event);
                }, Subscribers{});
        }

        template<typename Settings, typename Event>
        void receive(Manager<Settings>* manager, Event event) { }

        void register_entity(EntityID id) {
            m_registered_entities.insert(id);
        }

        void unregister_entity(EntityID id) {
            m_registered_entities.remove(id);
        }

        inline void resize(unsigned size) {
            m_registered_entities.resize(size);
        }

        SparseSet<EntityID> &get_registered_entities() {
            return m_registered_entities;
        }

    protected:
        SparseSet<EntityID> m_registered_entities;
    };
} // namespace ecs

#endif
