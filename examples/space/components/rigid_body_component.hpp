#pragma once

#include <glm/glm.hpp>

namespace ecs
{
    struct RigidBodyComponent
    {
       glm::vec3 velocity;
       float mass;
    };
} // namespace ecs
