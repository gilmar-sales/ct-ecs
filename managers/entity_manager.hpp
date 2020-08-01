#pragma once

#include <vector>

#include "../core/type_defs.hpp"

namespace ecs {
    template<typename TSettings>
    class EntityManager {
        using Settings = TSettings;

        using Bitset = typename Settings::Bitset;
    public:
        EntityManager(unsigned int size) : m_next_id{0}, m_signatures(size) { }
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

        template<typename T>
        bool has_component(EntityID id)
        {
            return m_signatures[id][Settings::template component_bit<T>()];
        }

        template<typename T>
        void add_component(EntityID id)
        {
            m_signatures[id][Settings::template component_bit<T>()] = 1;
        }

        template<typename T>
        void remove_component(EntityID id)
        {
            m_signatures[id][Settings::template component_bit<T>()] = 0;
        }

        template<typename T>
        void add_tag(EntityID id)
        {
            m_signatures[id][Settings::template tag_bit<T>()] = 1;
        }

        template<typename T>
        void remove_tag(EntityID id)
        {
            m_signatures[id][Settings::template tag_bit<T>()] = 0;
        }

        template<typename T>

        bool has_tag(EntityID id)
        {
            return m_signatures[id][Settings::template tag_bit<T>()];
        }

        const Bitset& get_signature(EntityID id) 
        {
            return m_signatures[id];
        }

        void grow(unsigned size)
        {
            m_signatures.resize(size);
        }

        EntityID get_last_entity()
        {
            return m_next_id - 1;
        }

    private:
        EntityID m_next_id;
        std::vector<Bitset> m_signatures;
    };
}