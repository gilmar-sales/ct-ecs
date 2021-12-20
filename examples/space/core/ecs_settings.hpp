#pragma once

#include <ecs/ecs.hpp>

#include "../systems/physics_system.hpp"
#include "../systems/render_system.hpp"
#include "../systems/player_move_system.hpp"
#include "../systems/meteor_manager_system.hpp"
#include "../systems/shoot_system.hpp"
#include "../systems/decay_system.hpp"

#include "../components/transform_component.hpp"
#include "../components/mesh_component.hpp"
#include "../tags/tags.hpp"

using ComponentList = std::tuple<ecs::TransformComponent, ecs::MeshComponent, ecs::RigidBodyComponent, ecs::DecayComponent>;
using TagList = std::tuple<ecs::PlayerTag>;
using SystemList = std::tuple<ecs::PhysicsSystem, ecs::RenderSystem, ecs::PlayerMoveSystem, ecs::MeteorManagerSystem, ecs::ShootSystem, ecs::DecaySystem>;
using Settings = ecs::Settings<ComponentList, TagList, SystemList>;
using ECSManager = ecs::Manager<Settings>;