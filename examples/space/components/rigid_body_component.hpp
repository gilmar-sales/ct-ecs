#ifndef SPACE_ECS_RIGIDBODY_COMPONENT_HPP
#define SPACE_ECS_RIGIDBODY_COMPONENT_HPP

#include <glm/glm.hpp>

namespace ecs {

    struct RigidBodyComponent {
        glm::vec3 velocity;
        float mass;
    };

} // namespace ecs

#endif // SPACE_ECS_RIGIDBODY_COMPONENT_HPP
