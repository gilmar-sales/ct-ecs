#pragma once

#include <bitset>

namespace ecs
{
    template <typename TComponentList, typename TTagList, typename TSystemList>
    struct Settings
    {
        using ComponentList = TComponentList;
        using TagList = TTagList;
        using SystemList = TSystemList;
        using ThisType = Settings<ComponentList, TagList, SystemList>;

        template <typename T>
        static constexpr bool is_component() noexcept
        {
            return mp::contains<T, ComponentList>{};
        }
        template <typename T>
        static constexpr bool is_tag() noexcept
        {
            return mp::contains<T, TagList>{};
        }

        static constexpr std::size_t component_count() noexcept
        {
            return mp::size_of<ComponentList>();
        }
        static constexpr std::size_t tag_count() noexcept
        {
            return mp::size_of<TagList>();
        }

        template <typename T>
        static constexpr std::size_t component_id() noexcept
        {
            return mp::index_of<T, ComponentList>();
        }
        template <typename T>
        static constexpr std::size_t tag_id() noexcept
        {
            return mp::index_of<T, TagList>();
        }

        using Bitset = std::bitset<component_count() + tag_count()>;

        template <typename T>
        static constexpr std::size_t component_bit() noexcept
        {
            return component_id<T>();
        }
        template <typename T>
        static constexpr std::size_t tag_bit() noexcept
        {
            return component_count() + tag_id<T>();
        }
    };
} // namespace ecs
