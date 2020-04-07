#pragma once

#include "component_manager.hpp"
#include "entity_manager.hpp"

namespace ecs
{

    /* The Manager class will be responsible to control the others managers
    * and run all the systems
    */    
   template <typename TSettings>
    class Manager
    {
        using Settings = TSettings;

        using ComponentList = typename Settings::ComponentList;
        using TagList = typename Settings::TagList;
        using SystemList = typename Settings::SystemList;
        using Bitset = typename Settings::Bitset;

        using SystemsContainer = mp::rename<std::tuple, SystemList>;
    public:
        Manager(unsigned size) : m_entities(size), m_components(size)
        {
            
        };
        ~Manager() = default;

        EntityID create_entity()
        {
            return m_entities.create_entity();
        }

        void destroy_entity(EntityID id)
        {
            m_components.move_data(m_entities.get_last_entity(), id);
            m_entities.destroy_entity(id);
        }

        template<typename T>
        T& get_component(EntityID id)
        {
            return m_components.template get_component<T>(id);
        }

    private:
        EntityManager<Settings> m_entities;
        ComponentManager<Settings> m_components;
        SystemsContainer m_systems;
    };
    
} // namespace ecs