#pragma once

#include <vector>
#include <tuple>

#include "../core/type_defs.hpp"
#include "../../dependencies/mp/types/types_list.hpp"

namespace ecs
{
    template <typename TSettings>
    class ComponentManager
    {
        using Settings = TSettings;
        using ComponentList = typename Settings::ComponentList;

        template<typename... Ts>
        using TupleOfVectors = std::tuple<std::vector<Ts>...>;

    public:
        ComponentManager(unsigned long size)
        {
            resize(size);
        }
        ~ComponentManager() {}
    
        void resize(size_t new_size)
        {
            mp::for_tuple([this, new_size] (auto& vector)
            {
                vector.resize(new_size);
            }, m_vectors);
        }

        template <typename T>
        T& get_component(EntityID id)
        {
            return std::get<std::vector<T>>(m_vectors)[id];
        }

        void move_data(EntityID from, EntityID to)
        {
            mp::for_tuple([this, from, to] (auto& vector)
            {
                vector[to] = vector[from];
            }, m_vectors);
        }
    private:
        mp::rename<TupleOfVectors, ComponentList> m_vectors;
    };
} // namespace ecs
