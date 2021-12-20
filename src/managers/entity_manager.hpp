#pragma once

#include <vector>
#include <functional>

#include "../core/type_defs.hpp"

namespace ecs
{

    /**
     * @brief The EntityManager will create entity ids and keep them contiguous
     *
     * @tparam TSettings
     */
    template <typename TSettings>
    class EntityManager
    {
        using Settings = TSettings;

        using Bitset = typename Settings::Bitset;

    public:
        EntityManager(unsigned int size) : m_next_entity{0}, m_signatures(size) {}
        ~EntityManager() = default;

        EntityID create_entity()
        {
            return m_next_entity++;
        }

        void destroy_entity(EntityID id)
        {
            if (m_next_entity > 1)
            {
                m_signatures[id] = m_signatures[m_next_entity - 1];
                m_signatures[m_next_entity - 1].reset();
            }
            else
            {
                m_signatures[id].reset();
            }
            m_next_entity--;
        }

        template <typename T>
        bool has_component(EntityID id)
        {
            return m_signatures[id][Settings::template component_bit<T>()];
        }

        template <typename T>
        void add_component(EntityID id)
        {
            m_signatures[id][Settings::template component_bit<T>()] = 1;
        }

        template <typename T>
        void remove_component(EntityID id)
        {
            m_signatures[id][Settings::template component_bit<T>()] = 0;
        }

        template <typename T>
        void add_tag(EntityID id)
        {
            m_signatures[id][Settings::template tag_bit<T>()] = 1;
        }

        template <typename T>
        void remove_tag(EntityID id)
        {
            m_signatures[id][Settings::template tag_bit<T>()] = 0;
        }

        template <typename T>

        bool has_tag(EntityID id)
        {
            return m_signatures[id][Settings::template tag_bit<T>()];
        }

        const Bitset &get_signature(EntityID id)
        {
            return m_signatures[id];
        }

        void resize(unsigned size)
        {
            m_signatures.resize(size);
        }

        EntityID get_next_entity()
        {
            return m_next_entity;
        }

        inline void for_each(std::function<void(EntityID)> function)
        {
            for (EntityID entity = 0; entity < m_next_entity; entity++)
            {
                function(entity);
            }
        }

    private:
        EntityID m_next_entity;
        std::vector<Bitset> m_signatures;
    };
}