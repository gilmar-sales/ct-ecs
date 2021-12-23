#ifndef SPACE_WINDOW_HPP
#define SPACE_WINDOW_HPP

#include <string>
#include <iostream>

#include<glad/glad.h>
#include <GLFW/glfw3.h>

struct WindowData {
    std::string title;
    int width;
    int height;
};

class Window {
public:
    Window(const std::string &title, int width, int height);

    ~Window();

    GLFWwindow *get_native_window() { return native_window; }

    int get_window_width() { return data.width; }

    int get_window_height() { return data.height; }

    std::string get_title() const { return data.title; }

    void update();

private:
    WindowData data;
    GLFWwindow *native_window;

    void update_size(int width, int height);
};

#endif // SPACE_WINDOW_HPP
