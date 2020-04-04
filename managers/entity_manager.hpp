#pragma once

#include <bitset>
#include <vector>
#include <tuple>
#include <queue>

#include "entities/entity.hpp"

namespace ecs {
    template<typename TSettings>
    class EntityManager {
        using Settings = TSettings;

        using Bitset = Settings::Bitset;
    public:
        EntityManager(unsigned int size) : m_next_id(0), m_signatures(size) { }
        ~EntityManager() = default;

        EntityID create_entity()
        {
            return m_next_id++;
        } 

        void destroy_entity(EntityID id)
        {
            m_signatures[id] = m_signatures[m_next_id];
            m_signatures[m_next_id].reset();
            m_next_id--;
        }

        void set_signature(EntityID id, Bitset signature)
        {
            m_signatures[id] = signature;
        }

        Bitset& get_signature(EntityID) const
        {
            m_signatures[id];
        }

        void grow(unsigned size)
        {
            m_signatures.resize(size);
        }

    private:
        EntityID m_next_id;
        std::vector<Bitset> m_signatures;
    };
}