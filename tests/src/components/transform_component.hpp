//
// Created by gilmar on 12/21/21.
//

#ifndef CT_ECS_TRANSFORM_COMPONENT_HPP
#define CT_ECS_TRANSFORM_COMPONENT_HPP

#include <glm/glm.hpp>

struct TransformComponent {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
};

#endif //CT_ECS_TRANSFORM_COMPONENT_HPP
