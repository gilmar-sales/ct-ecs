#include "input.hpp"

#include "application.hpp"

bool Input::GetKeyDown(KeyCode key)
{
    int last_state = keys[key];
    auto *window = Application::get().get_window().get_native_window();
    auto state = glfwGetKey(window, static_cast<int>(key));
    bool key_down = last_state == GLFW_RELEASE && state == GLFW_PRESS;

    keys[key] = state;
    return key_down;
}

bool Input::GetKeyUp(KeyCode key)
{
    int last_state = keys[key];
    auto *window = Application::get().get_window().get_native_window();
    auto state = glfwGetKey(window, static_cast<int>(key));
    bool key_down = last_state != GLFW_RELEASE && state == GLFW_RELEASE;

    keys[key] = state;
    return key_down;
}

bool Input::IsKeyPressed(const KeyCode key)
{
    auto *window = Application::get().get_window().get_native_window();
    auto state = glfwGetKey(window, static_cast<int32_t>(key));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(const MouseCode button)
{
    auto *window = Application::get().get_window().get_native_window();
    auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
    return state == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition()
{
    auto *window = Application::get().get_window().get_native_window();
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return {(float)xpos, (float)ypos};
}

float Input::GetMouseX()
{
    return GetMousePosition().x;
}

float Input::GetMouseY()
{
    return GetMousePosition().y;
}
