#pragma once

#include <vector>
#include <functional>
#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Entity {
    unsigned id;
    glm::vec2 position;
    float radius;
};

class QuadTree {
public:
    QuadTree(glm::vec2 position, float half_range, unsigned capacity);
    ~QuadTree() = default;

    bool insert(Entity entity);
    void subdivide();
    void query(Entity entity, std::vector<Entity>* found);
    bool contains(Entity entity);
    bool collide(Entity first, Entity second);
    bool intersect(Entity entity);
    void draw(unsigned vao, unsigned shaderProgram);

private:
    glm::vec2 m_position;
    float m_half_range;
    std::vector<Entity> m_elements;
    unsigned m_capacity;

    std::unique_ptr<QuadTree> m_top_left;
    std::unique_ptr<QuadTree> m_top_right;
    std::unique_ptr<QuadTree> m_bot_left;
    std::unique_ptr<QuadTree> m_bot_right;
};
