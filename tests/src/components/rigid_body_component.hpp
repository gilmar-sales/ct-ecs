//
// Created by gilmar on 12/21/21.
//

#ifndef RIGID_BODY_COMPONENT_HPP
#define RIGID_BODY_COMPONENT_HPP

#include <glm/glm.hpp>

struct RigidBodyComponent {
    glm::vec3 velocity;
    float mass;
};

#endif //RIGID_BODY_COMPONENT_HPP
