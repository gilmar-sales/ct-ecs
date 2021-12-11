#include "core/application.hpp"

int main(int argc, char const *argv[])
{
    Application app = Application();

    app.run();
    
    std::cout << "completed" << std::endl;
    return 0;
}
