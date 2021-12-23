//
// Created by gilmar on 12/21/21.
//

#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

#include <glm/glm.hpp>

struct TransformComponent {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
};

#endif //TRANSFORM_COMPONENT_HPP
