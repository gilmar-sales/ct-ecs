#pragma once

#include <tuple>
#include <set>

#include "../dependencies/mp/types/types_list.hpp"
#include "../entities/entity.hpp"

namespace ecs
{
    template<typename Derived>
    class BaseSystem
    {
    public:
        BaseSystem() : m_registered_entities()
        {
        }

        void update(float delta_time)
        {
            static_cast<Derived*>(this)->update(delta_time);
        }

        void register_entity(EntityID id)
        {
            m_registered_entities.insert(id);
        }
        //auto& get_signature() const { return m_signature; }

    protected:
        std::set<EntityID> m_registered_entities;
    };
}