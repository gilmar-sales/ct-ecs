#ifndef CT_ECS_MANAGER_HPP
#define CT_ECS_MANAGER_HPP

#include "component_manager.hpp"
#include "entity_manager.hpp"
#include "../core/sparse_set.hpp"

namespace ecs {

    /**
     * @brief The Manager class will be responsible to orchestrate the others managers
     * like: resize all manager if it's needed, run the systems, forward components
     *
     * @tparam TSettings
     */
    template<typename TSettings>
    class Manager {
    public:
        using Settings = TSettings;

        using ComponentList = typename Settings::ComponentList;
        using TagList = typename Settings::TagList;
        using SystemList = typename Settings::SystemList;
        using Bitset = typename Settings::Bitset;

        using SystemsContainer = mp::rename<std::tuple, SystemList>;
        using SignaturesContainer = mp::generate_tuple<Bitset, mp::size_of<SystemList>()>;

        Manager(unsigned capacity = 1024) : m_entities(capacity), m_components(capacity), m_capacity(capacity) {
            initialize_signatures();

            // initialize systems
            mp::for_tuple([this, capacity](auto &system) { system.resize(capacity); },
                          m_systems);
        };

        ~Manager() = default;

        EntityID create_entity() {
            if (get_next_entity() >= m_capacity)
                resize(m_capacity * 2);

            m_components.reset_components(get_next_entity());

            return m_entities.create_entity();
        }

        EntityID get_next_entity() { return m_entities.get_next_entity(); }

        void destroy_entity(EntityID id) {
            auto last_entity = m_entities.get_next_entity() - 1;
            mp::for_tuple([this, id, last_entity](auto &system) {
                              using system_t = std::remove_reference_t<decltype(system)>;

                              auto &sys_sig = std::get<mp::index_of<system_t, SystemList>()>(m_signatures);

                              system.unregister_entity(id);
                              system.unregister_entity(last_entity);
                          },
                          m_systems);

            if (id < last_entity) {
                mp::for_tuple([this, id, last_entity](auto &system) {
                                  using system_t = std::remove_reference_t<decltype(system)>;

                                  auto &sys_sig = std::get<mp::index_of<system_t, SystemList>()>(m_signatures);

                                  if ((sys_sig & m_entities.get_signature(last_entity)) == sys_sig) {
                                      system.register_entity(id);
                                      system.unregister_entity(last_entity);
                                  }
                              },
                              m_systems);

                m_components.move_data(last_entity, id);
            }
            m_entities.destroy_entity(id);
        }

        [[nodiscard]] Bitset &get_entity_signature(EntityID entity) {
            return m_entities.get_signature(entity);
        };

        template<typename TSystem>
        TSystem& get_system() {
            return std::get<mp::index_of<TSystem, SystemList>()>(m_systems);
        }

        template<typename TSystem>
        Bitset get_system_signature() {
            return std::get<mp::index_of<TSystem, SystemList>()>(m_signatures);
        }

        template<typename TSystem>
        SparseSet<EntityID> &get_registered_entities() {
            return std::get<mp::index_of<TSystem, SystemList>()>(m_systems).get_registered_entities();
        }

        template<typename T>
        bool has_component(EntityID id) {
            return m_entities.template has_component<T>(id);
        }

        template<typename T>
        T &get_component(EntityID id) {
            return m_components.template get_component<T>(id);
        }

        template<typename T>
        T &add_component(EntityID id) {
            m_entities.template add_component<T>(id);

            mp::for_tuple([this, id](auto &system) {
                              using system_t = std::remove_reference_t<decltype(system)>;

                              auto &sys_sig = std::get<mp::index_of<system_t, SystemList>()>(m_signatures);

                              if ((sys_sig & m_entities.get_signature(id)) == sys_sig) {
                                  system.register_entity(id);
                              }
                          },
                          m_systems);

            return m_components.template get_component<T>(id);
        }

        template<typename T>
        T &add_component(EntityID id, T value) {
            m_entities.template add_component<T>(id);

            mp::for_tuple([this, id](auto &system) {
                              using system_t = std::remove_reference_t<decltype(system)>;

                              auto &sys_sig = std::get<mp::index_of<system_t, SystemList>()>(m_signatures);

                              if ((sys_sig & m_entities.get_signature(id)) == sys_sig) {
                                  system.register_entity(id);
                              }
                          },
                          m_systems);

            m_components.template set_component<T>(id, value);

            return m_components.template get_component<T>(id);
        }

        template<typename T>
        void remove_component(EntityID id) {
            m_entities.template remove_component<T>(id);

            mp::for_tuple([this, id](auto &system) {
                              using system_t = std::remove_reference_t<decltype(system)>;

                              auto &sys_sig = std::get<mp::index_of<system_t, SystemList>()>(m_signatures);

                              if ((sys_sig & m_entities.get_signature(id)) != sys_sig) {
                                  system.unregister_entity(id);
                              }
                          },
                          m_systems);
        }

        template<typename T>
        bool has_tag(EntityID id) {
            return m_entities.template has_tag<T>(id);
        }

        template<typename T>
        bool add_tag(EntityID id) {
            m_entities.template add_tag<T>(id);

            mp::for_tuple([this, id](auto &system) {
                              using system_t = std::remove_reference_t<decltype(system)>;

                              auto &sys_sig = std::get<mp::index_of<system_t, SystemList>()>(m_signatures);

                              if ((sys_sig & m_entities.get_signature(id)) == sys_sig) {
                                  system.register_entity(id);
                              }
                          },
                          m_systems);

            return true;
        }

        void update() {
            mp::for_tuple([this](auto &system) {
                              system.get_registered_entities().sort();
                              system.update(this);
                          },
                          m_systems);
        }

        inline void for_each(std::function<void(EntityID)> function) {
            m_entities.for_each(function);
        }

    private:
        void initialize_signatures() {

            mp::for_tuple([this](auto system) {
                              using System = decltype(system);
                              mp::for_tuple([this](auto sig) {
                                  using Sig = decltype(sig);

                                  if (Settings::template is_component<Sig>())
                                      std::get<mp::index_of<System, SystemsContainer>()>(
                                              m_signatures)[Settings::template component_bit<Sig>()] = 1;
                                  else if (Settings::template is_tag<Sig>())
                                      std::get<mp::index_of<System, SystemsContainer>()>(
                                              m_signatures)[Settings::template tag_bit<Sig>()] = 1;

                              }, typename System::Signature{});
                          },
                          m_systems);
        }

        void resize(unsigned size) {
            m_entities.resize(size);
            m_components.resize(size);

            // resize systems
            mp::for_tuple([this, size](auto &system) { system.resize(size); },
                          m_systems);

            m_capacity = size;
        }

        EntityManager <Settings> m_entities;
        ComponentManager <Settings> m_components;
        SystemsContainer m_systems;
        SignaturesContainer m_signatures;
        unsigned m_capacity;
    };

} // namespace ecs

#endif
