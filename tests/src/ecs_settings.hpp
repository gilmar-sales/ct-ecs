//
// Created by gilmar on 12/21/21.
//

#ifndef CT_ECS_ECS_SETTINGS_HPP
#define CT_ECS_ECS_SETTINGS_HPP
#include <ecs/ecs.hpp>

#include "tags/player_tag.hpp"
#include "components/name_component.hpp"
#include "systems/physics_system.hpp"

using ComponentList = std::tuple<TransformComponent, NameComponent>;
using TagList = std::tuple<PlayerTag>;
using SystemList = std::tuple<PhysicsSystem>;
using Settings = ecs::Settings<ComponentList, TagList, SystemList>;
using ECSManager = ecs::Manager<Settings>;
#endif //CT_ECS_ECS_SETTINGS_HPP
