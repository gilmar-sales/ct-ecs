#pragma once

#include <set>

#include "../dependencies/mp/types/types_list.hpp"
#include "../core/type_defs.hpp"

namespace ecs
{
    template<typename Derived>
    class BaseSystem
    {
    public:
        BaseSystem() : m_registered_entities()
        {
            
        }

        void update()
        {
            static_cast<Derived*>(this)->update();
        }

        void register_entity(EntityID id)
        {
            m_registered_entities.insert(id);
        }

        void unregister_entity(EntityID id)
        {
            m_registered_entities.erase(id);
        }

    protected:
        std::set<EntityID> m_registered_entities;
    };
}
