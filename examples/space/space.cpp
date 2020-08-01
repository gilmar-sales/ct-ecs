#include "../../ecs.hpp"

#include "systems/physics_sytem.hpp"

#include "components/transform_component.hpp"
#include "tags/tags.hpp"

using ComponentList = std::tuple<ecs::TransformComponent>;
using TagList = std::tuple<ecs::PlayerTag>;
using SystemList = std::tuple<ecs::PhysicsSystem>;
using Settings = ecs::Settings<ComponentList, TagList, SystemList>;
using ECSManager = ecs::Manager<Settings>;

int main(int argc, char const *argv[])
{
    ECSManager mgr = ECSManager(100);
    
    auto ent = mgr.create_entity(); 

    mgr.add_component<ecs::TransformComponent>(ent);
    
    for(int i = 0; i < 1000000; i++)
        mgr.update();


    std::cout << "completed" << std::endl;
    return 0;
}
