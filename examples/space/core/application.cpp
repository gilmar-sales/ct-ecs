#include "application.hpp"
#include "time.hpp"
#include <GLFW/glfw3.h>
#include <sstream>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>

#include "../tags/tags.hpp"

Application *Application::instance = nullptr;

Application::Application() : window("Space", 800, 600), mgr(ECSManager()) {
    assert(!instance);
    instance = this;

    init_player();
    glfwSwapInterval(0);
}

void Application::run() {
    float previous_time = glfwGetTime();
    float frametime_accumulator = 0;
    float frames = 0;
    while (!glfwWindowShouldClose(window.get_native_window())) {

        float now = glfwGetTime();
        Time::delta_time = now - previous_time;
        previous_time = now;

        frametime_accumulator += Time::delta_time;
        frames += 1;

        if (frametime_accumulator >= 1) {
            if (get_manager().get_next_entity()) {
                auto &player = mgr.add_component<ecs::PlayerComponent>(0);
                std::stringstream ss;
                ss << window.get_title() << " - " << frames << " FPS" << " - Lifes: " << player.lifes << " - Score: "
                   << player.score << " - Entities: ";
                ss << mgr.get_next_entity();

                glfwSetWindowTitle(window.get_native_window(), ss.str().c_str());
            }

            frametime_accumulator = 0;
            frames = 0;
        }

        window.update();

        mgr.update();
        glfwSwapBuffers(window.get_native_window());
    }
}

void Application::init_player() {

    auto ent = mgr.create_entity();

    auto &transform = mgr.add_component<ecs::TransformComponent>(ent);
    auto &mesh = mgr.add_component<ecs::MeshComponent>(ent);
    auto &rigidbody = mgr.add_component<ecs::RigidBodyComponent>(ent);
    auto &circle_collider = mgr.add_component<ecs::CircleColliderComponent>(ent);
    auto &life = mgr.add_component<ecs::PlayerComponent>(ent);
    mgr.add_tag<ecs::PlayerTag>(ent);

    transform.position = {0, 0, 0};
    transform.scale = {20, 20, 20};
    transform.rotation = {0, 0, 0};

    mesh.VAO = MeshAsset::get_triangle_mesh();
    rigidbody.mass = 2;
    circle_collider.radius = 10;
    life.lifes = 4;
}

