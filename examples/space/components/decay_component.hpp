#ifndef SPACE_ECS_DECAY_COMPONENT_HPP
#define SPACE_ECS_DECAY_COMPONENT_HPP

namespace ecs {

    struct DecayComponent {
        float max_time;
        float current;
    };

} // namespace ecs

#endif // SPACE_ECS_DECAY_COMPONENT_HPP
