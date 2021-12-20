#include "quadtree.hpp"

#include <iostream>

QuadTree::QuadTree(glm::vec2 position, float half_range, unsigned capacity)
{
    m_position = position;
    m_half_range = half_range;
    m_elements = std::vector<Entity>(0);
    m_elements.reserve(capacity);
    m_capacity = capacity;

    m_top_left = nullptr;
    m_top_right = nullptr;
    m_bot_left = nullptr;
    m_bot_right = nullptr;
}

bool QuadTree::insert(Entity entity)
{
    if (!contains(entity))
    {
        return false;
    }

    if (m_elements.size() < m_capacity)
    {
        m_elements.push_back(entity);
        return true;
    } else if (m_top_left == nullptr) {
        subdivide();
    }

    return (
        m_top_left->insert(entity) ||
        m_top_right->insert(entity) ||
        m_bot_left->insert(entity) ||
        m_bot_right->insert(entity)
    );
}

void QuadTree::subdivide()
{
    float half_range = m_half_range / 2;

    glm::vec2 top_left_pos = m_position-half_range; 
    glm::vec2 top_right_pos = {m_position.x+half_range, m_position.y-half_range}; 
    glm::vec2 bot_left_pos = {m_position.x-half_range, m_position.y+half_range}; 
    glm::vec2 bot_right_pos = m_position+half_range; 

    m_top_left = std::make_unique<QuadTree>(top_left_pos, half_range, m_capacity);
    m_top_right = std::make_unique<QuadTree>(top_right_pos, half_range, m_capacity);
    m_bot_left = std::make_unique<QuadTree>(bot_left_pos, half_range, m_capacity);
    m_bot_right = std::make_unique<QuadTree>(bot_right_pos, half_range, m_capacity);
}

void QuadTree::query(Entity entity, std::vector<Entity>* found)
{
    if (!intersect(entity))
    {
        return;
    }

    for (unsigned i = 0; i < m_elements.size(); i++)
    {
        if(entity.id == m_elements[i].id)
            continue;

        if (collide(entity, m_elements[i]))
        {
            found->push_back(m_elements[i]);
        }
    }

    if (m_top_left)
    {
        m_top_left->query(entity, found);
        m_top_right->query(entity, found);
        m_bot_left->query(entity, found);
        m_bot_right->query(entity, found);
    }
}

bool QuadTree::contains(Entity entity)
{
    return (
        entity.position.x >= m_position.x - m_half_range &&
        entity.position.x <= m_position.x + m_half_range &&
        entity.position.y >= m_position.y - m_half_range &&
        entity.position.y <= m_position.y + m_half_range
    );
}

bool QuadTree::collide(Entity first, Entity second) 
{
    float distance = glm::distance(first.position, second.position);
    return (
        distance <= first.radius + second.radius
    );
}

bool QuadTree::intersect(Entity entity)
{
    return (
        entity.position.x >= m_position.x - (m_half_range + entity.radius) &&
        entity.position.x <= m_position.x + (m_half_range + entity.radius) &&
        entity.position.y >= m_position.y - (m_half_range + entity.radius) &&
        entity.position.y <= m_position.y + (m_half_range + entity.radius)
    );
}

void QuadTree::draw(unsigned vao, unsigned shaderProgram)
{
    static float color[3] = {1.f,1.f,1.f};
    glm::mat4 model          = glm::mat4(1.0f);
    model       = glm::translate(model, glm::vec3(m_position, 0.0f));
    model       = glm::scale(model, glm::vec3(m_half_range, m_half_range, 0.0f));

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, &color[0]);
    glBindVertexArray(vao);
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);

    if(m_top_left)
    {
        m_top_left->draw(vao, shaderProgram);
        m_top_right->draw(vao, shaderProgram);
        m_bot_left->draw(vao, shaderProgram);
        m_bot_right->draw(vao, shaderProgram);
    }
}
