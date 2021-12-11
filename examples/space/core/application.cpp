#include "application.hpp"
#include "time.hpp"
#include <GLFW/glfw3.h>


Application::Application(): window("Space", 800, 600), mgr(ECSManager())
{
    auto ent = mgr.create_entity();

    ecs::TransformComponent& transform = mgr.add_component<ecs::TransformComponent>(ent);
    ecs::MeshComponent& mesh = mgr.add_component<ecs::MeshComponent>(ent);

    transform.position = {0,0,0};
    transform.scale = {15,15,15};
    transform.rotation = {1,1,1};

    mesh.VAO = initTriangleMesh();
}

Application::~Application()
{
}

void Application::run() {
    float previous_time = glfwGetTime();
    while(!glfwWindowShouldClose(window.get_native_window())) {
        float now = glfwGetTime();
        Time::delta_time = now - previous_time;

        window.update();

        mgr.update();
        glfwSwapBuffers(window.get_native_window());
    }
}