#pragma once

#include "component_manager.hpp"
#include "entity_manager.hpp"

/* Class Manager
 * 
 * 
 */

namespace ecs
{
    template <typename TSettings>
    class Manager
    {
        using Settings = TSettings;
        using Bitset = typename Settings::Bitset;

    public:
        Manager();
        ~Manager();
    private:
        EntityManager<Settings> m_entities;
        ComponentManager<Settings> m_components;
    };
    
} // namespace ecs