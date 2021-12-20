#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace ecs
{
    struct TransformComponent
    {
        glm::vec3 position = {0, 0, 0};
        glm::vec3 scale = {1, 1, 1};
        glm::vec3 rotation = {0, 0, 0};

        glm::vec3 get_forward_direction()
        {
            glm::vec4 front = {0, 1, 0, 0};
            glm::mat4 rotation_matrix = {
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}};
            rotation_matrix = glm::rotate(rotation_matrix, glm::radians(rotation.z), {0, 0, 1});
            front = front * rotation_matrix;

            return glm::normalize(glm::vec3(-front.x, front.y, front.z));
        }
    };

} // namespace ecs
