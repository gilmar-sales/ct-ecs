//
// Created by gilmar on 12/21/21.
//

#ifndef CT_ECS_RIGID_BODY_COMPONENT_HPP
#define CT_ECS_RIGID_BODY_COMPONENT_HPP

#include <glm/glm.hpp>

struct RigidBodyComponent
{
    glm::vec3 velocity;
    float mass;
};

#endif //CT_ECS_RIGID_BODY_COMPONENT_HPP
