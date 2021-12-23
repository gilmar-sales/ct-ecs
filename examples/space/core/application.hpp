#ifndef SPACE_APPLICATION_HPP
#define SPACE_APPLICATION_HPP

#include "window.hpp"
#include "ecs_settings.hpp"

class Application {
public:
    Application();

    ~Application() = default;

    static Application &get() { return *instance; }

    static ECSManager &get_manager() { return instance->mgr; }

    void run();

    void init_player();

    Window &get_window() { return window; }

private:
    Window window;
    ECSManager mgr;
    static Application *instance;

};

#endif // SPACE_APPLICATION_HPP
