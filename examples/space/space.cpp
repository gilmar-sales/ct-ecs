#include "../../include/ecs/ecs.hpp"

#include "systems/physics_system.hpp"

#include "components/transform_component.hpp"
#include "tags/tags.hpp"

using ComponentList = std::tuple<ecs::TransformComponent>;
using TagList = std::tuple<ecs::PlayerTag>;
using SystemList = std::tuple<ecs::PhysicsSystem>;
using Settings = ecs::Settings<ComponentList, TagList, SystemList>;
using ECSManager = ecs::Manager<Settings>;

int main(int argc, char const *argv[])
{
    ECSManager mgr = ECSManager();
    
    
    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < 1000; j++) {
            auto ent = mgr.create_entity(); 

            mgr.add_component<ecs::TransformComponent>(ent, {1.f,2.f,3.f});
            if (j > 800) {
                mgr.destroy_entity(400);
            }
        }
        mgr.update();
    }

    std::cout << "completed" << std::endl;
    return 0;
}
