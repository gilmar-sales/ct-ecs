#pragma once

#include <glm/glm.hpp>

namespace ecs
{
    struct TransformComponent
    {
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;
    };
    
} // namespace ecs
