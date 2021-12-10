#pragma once

#include <string>
#include <iostream>

#include<glad/glad.h>
#include <GLFW/glfw3.h>

struct WindowData {
    std::string title;
    unsigned width;
    unsigned height;
};

class Window
{
public:
    Window(std::string title, unsigned width, unsigned height);
    ~Window();
private:
    WindowData data;
    GLFWwindow* native_window;

    void update_size(int width, int height);
};
