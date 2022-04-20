#ifndef SPACE_ECS_SHOOT_COMPONENT_HPP
#define SPACE_ECS_SHOOT_COMPONENT_HPP

namespace ecs {
    struct LaserGunComponent {
        float time = 0;
        unsigned current_shots = 0;
        unsigned max_shots_per_second = 2;
    };
}

#endif //SPACE_ECS_SHOOT_COMPONENT_HPP
