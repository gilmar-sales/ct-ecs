#ifndef __application_hpp__
#define __application_hpp__

#include "window.hpp"
#include "ecs_settings.hpp"

class Application
{
private:
    Window window;
    ECSManager mgr;
    static Application *instance;

public:
    Application();
    ~Application();

    static Application &get() { return *instance; }
    static ECSManager &get_manager() { return instance->mgr; }

    void run();
    void init_player();

    Window &get_window() { return window; }
};

#endif
