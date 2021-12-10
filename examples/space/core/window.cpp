#include "window.hpp"

Window::Window(std::string title, unsigned width, unsigned height): data({title, width, height})
{
    int glfw_status = glfwInit();

    if (!glfw_status) {
        std::cout << "Couldn't initialize GLFW!\n";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    native_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(native_window, this);

    glfwMakeContextCurrent(native_window);

    int glad_status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    if(!glad_status) {
        std::cout << "Couldn't initialize GLAD!\n";
    }

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(native_window, [](GLFWwindow* native_window, int width, int height) {
        Window* window = (Window*) glfwGetWindowUserPointer(native_window);
        window->update_size(width, height);
    });
}

void Window::update_size(int width, int height) {
    data.width = width;
    data.height = height;

    glViewport(0, 0, width, height);
}

Window::~Window()
{
    glfwDestroyWindow(native_window);
    glfwTerminate();
}
