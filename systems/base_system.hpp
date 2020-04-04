#pragma once

#include <tuple>
#include <vector>

#include "../dependencies/mp/types/types_list.hpp"
#include "../entities/entity.hpp"

    template<typename TSettings, typename TSignature, typename Derived>
    class BaseSystem
    {
    public:
        using Settings = TSettings;
        using ComponentList = typename Settings::ComponentList;
        using TagList = typename Settings::TagList;
        using Bitset = typename Settings::Bitset;
        using Signature = TSignature;

        BaseSystem() : m_registered_entities()
        {
            ComponentList comps{};
            TagList tags{};
            mp::for_tuple([this] (auto comp)
            {
                using Component = decltype(comp);

                if(mp::contains<Component, Signature>{})
                    this->m_signature[Settings::template component_bit<Component>()] = true;
            }, comps);

            mp::for_tuple([this] (auto tag) {
                using Tag = decltype(tag);

                if(mp::contains<Tag, Signature>{})
                    this->m_signature[Settings::template tag_bit<Tag>()] = true;
            }, tags);
        }

        void update(Signature& signature)
        {
            static_cast<Derived*>(this)->update(signature);
        }

        auto& get_signature() const { return m_signature; }

    private:
        std::vector<EntityID> m_registered_entities;
        Bitset m_signature;
    };
