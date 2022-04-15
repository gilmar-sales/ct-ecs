#include "window.hpp"

#include <iostream>

Window::Window(const std::string &title, int width, int height) : data({title, width, height}) {
    int glfw_status = glfwInit();

    if (!glfw_status) {
        std::cout << "Couldn't initialize GLFW!\n";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    native_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!native_window) {
        std::cout << "Couldn't initialize GLAD!\n";
    }

    glfwSetWindowUserPointer(native_window, this);

    glfwMakeContextCurrent(native_window);

    int glad_status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    if (!glad_status) {
        std::cout << "Couldn't initialize GLAD!\n";
    }

    std::cout << glfwGetVersionString() << std::endl;

    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSetFramebufferSizeCallback(native_window, [](GLFWwindow *glfw_window, int width, int height) {
        auto *window = (Window *) glfwGetWindowUserPointer(glfw_window);
        window->update_size(width, height);
    });

    glfwSetWindowCloseCallback(native_window, [](GLFWwindow *glfw_window) {
        glfwSetWindowShouldClose(glfw_window, 1);
    });

    glfwSetWindowSizeCallback(native_window, [](GLFWwindow* glfw_window, int width, int height){
        auto *window = (Window *) glfwGetWindowUserPointer(glfw_window);
        window->update_size(width, height);
    });
}

Window::~Window() {
    glfwDestroyWindow(native_window);
    glfwTerminate();
}

void Window::update() {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwPollEvents();
}

void Window::update_size(int width, int height) {
    data.width = width;
    data.height = height;

    glViewport(0, 0, width, height);
}

