#include "application.hpp"
#include "time.hpp"
#include <GLFW/glfw3.h>
#include <sstream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

#include "../tags/tags.hpp"

Application *Application::instance = nullptr;

Application::Application() : window("Space", 800, 600), mgr(ECSManager())
{
    assert(!instance);
    instance = this;

    init_player();
    init_meteor_manager();
    // glfwSwapInterval(2);
}

Application::~Application()
{
}

void Application::run()
{
    float previous_time = glfwGetTime();
    float frametime_accumulator = 0;
    float frames = 0;
    while (!glfwWindowShouldClose(window.get_native_window()))
    {

        float now = glfwGetTime();
        Time::delta_time = now - previous_time;
        previous_time = now;

        frametime_accumulator += Time::delta_time;
        frames += 1;

        if (frametime_accumulator >= 1)
        {
            std::stringstream ss;
            ss << window.get_title() << " - " << frames << " FPS - Entities: ";
            ss << mgr.get_next_entity();
            glfwSetWindowTitle(window.get_native_window(), ss.str().c_str());

            frametime_accumulator = 0;
            frames = 0;
        }

        window.update();

        mgr.update();
        glfwSwapBuffers(window.get_native_window());
    }
}

void Application::init_player()
{

    auto ent = mgr.create_entity();

    ecs::TransformComponent &transform = mgr.add_component<ecs::TransformComponent>(ent);
    ecs::MeshComponent &mesh = mgr.add_component<ecs::MeshComponent>(ent);
    ecs::RigidBodyComponent &rigidbody = mgr.add_component<ecs::RigidBodyComponent>(ent);
    ecs::CircleColliderComponent &circle_collider = mgr.add_component<ecs::CircleColliderComponent>(ent);
    mgr.add_tag<ecs::PlayerTag>(ent);

    transform.position = {0, 0, 0};
    transform.scale = {20, 20, 20};
    transform.rotation = {0, 0, 0};

    mesh.VAO = initTriangleMesh();
    rigidbody.mass = 2;
    circle_collider.radius = 10;
}

void Application::init_meteor_manager() 
{
    auto ent = mgr.create_entity();

    mgr.add_tag<ecs::EnemyTag>(ent);
}
