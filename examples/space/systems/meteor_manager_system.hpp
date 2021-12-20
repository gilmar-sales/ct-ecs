#pragma once
#include <iostream>
#include <random>

#include <ecs/ecs.hpp>

#include "../core/time.hpp"
#include "../core/input.hpp"

#include "../components/transform_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../components/decay_component.hpp"
#include "../components/circle_collider_component.hpp"
#include "../tags/tags.hpp"

class Application;

namespace ecs
{
    class MeteorManagerSystem : public BaseSystem<MeteorManagerSystem>
    {
    public:
        using Signature = std::tuple<ecs::EnemyTag>;

        MeteorManagerSystem() = default;
        ~MeteorManagerSystem() = default;

        template <typename T>
        void update(T &comps)
        {
            if (m_registered_entities.size() == 1)
            {
                for (int i = 0; i < current_wave; i++) {
                auto ent = Application::get_manager().create_entity();

                Application::get_manager().add_tag<ecs::EnemyTag>(ent);

                TransformComponent &transform = Application::get_manager().add_component<TransformComponent>(ent);
                RigidBodyComponent &rigidbody = Application::get_manager().add_component<RigidBodyComponent>(ent);
                MeshComponent &mesh = Application::get_manager().add_component<MeshComponent>(ent);
                CircleColliderComponent &collider = Application::get_manager().add_component<CircleColliderComponent>(ent);

                std::random_device rd; // obtain a random number from hardware
                std::mt19937 gen(rd()); // seed the generator
                std::uniform_int_distribution<> distrPos(-400, 400); // define the range
                std::uniform_int_distribution<> distrScale(10, 50); // define the rangev
                std::uniform_int_distribution<> distrAngle(0, 360); // define the rangev
                
                float x = distrPos(gen);
                float y = distrPos(gen);

                float angle = distrAngle(gen);

                float speed = distrScale(gen);
                float size = distrScale(gen);

                transform.position = {x, y, 0};
                transform.rotation = {0,0, angle};
                transform.scale = {size, size, size};
                
                rigidbody.velocity = glm::normalize(glm::vec3(x, y, 0)) * speed;
                rigidbody.mass = 0.f;

                mesh.VAO = Application::initCircleMesh();
                collider.radius = size;
            }

            int previous_wave = current_wave;
            current_wave = next_wave;
            next_wave += previous_wave;
            }
        }
    private:
        int current_wave = 5;
        int next_wave = 8;
    };

}
