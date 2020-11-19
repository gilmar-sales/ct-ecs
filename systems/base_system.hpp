#pragma once

#include "../dependencies/mp/types/types_list.hpp"
#include "../core/type_defs.hpp"
#include "../core/sparse_set.hpp"

namespace ecs
{
    template<typename Derived>
    class BaseSystem
    {
    public:
        BaseSystem(unsigned capacity = 1024u) : m_registered_entities(capacity)
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
            m_registered_entities.remove(id);
        }
        
        inline void resize(unsigned size)
        {
            m_registered_entities.resize(size);
        }

    protected:
        sparse_set<EntityID> m_registered_entities;
    };
}
