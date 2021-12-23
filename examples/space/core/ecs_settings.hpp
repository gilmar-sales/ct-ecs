#pragma once

#include <ecs/ecs.hpp>

#include "../systems/physics_system.hpp"
#include "../systems/render_system.hpp"
#include "../systems/player_move_system.hpp"
#include "../systems/meteor_manager_system.hpp"
#include "../systems/shoot_system.hpp"
#include "../systems/decay_system.hpp"
#include "../systems/collision_system.hpp"
#include "../systems/player_system.hpp"
#include "../tags/tags.hpp"

using ComponentList = std::tuple<ecs::PlayerComponent, ecs::TransformComponent, ecs::MeshComponent, ecs::RigidBodyComponent, ecs::DecayComponent, ecs::CircleColliderComponent, ecs::BulletComponent>;
using TagList = std::tuple<ecs::PlayerTag, ecs::EnemyTag, ecs::BulletTag>;
using SystemList = std::tuple<ecs::PhysicsSystem, ecs::RenderSystem, ecs::PlayerMoveSystem, ecs::MeteorManagerSystem, ecs::ShootSystem, ecs::DecaySystem, ecs::CollisionSystem, ecs::PlayerSystem>;
using Settings = ecs::Settings<ComponentList, TagList, SystemList>;
using ECSManager = ecs::Manager<Settings>;