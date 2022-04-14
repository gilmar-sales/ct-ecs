#ifndef SPACE_ECS_RENDER_SYSTEM_HPP
#define SPACE_ECS_RENDER_SYSTEM_HPP

#include <iostream>
#include <tuple>

#include <ecs/ecs.hpp>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../components/transform_component.hpp"
#include "../components/mesh_component.hpp"

#include "../shaders.h"

namespace ecs {
    class RenderSystem : public BaseSystem<RenderSystem> {
    public:
        using Signature = std::tuple<ecs::TransformComponent, ecs::MeshComponent>;

        RenderSystem(): color(1.0f, 1.0f, 1.0f) {

            // Initialize shaders
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexSource, nullptr);
            glCompileShader(vertexShader);
            checkShader(vertexShader);

            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
            glCompileShader(fragmentShader);
            checkShader(fragmentShader);

            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            int success;
            char infoLog[512];
            // check for linking errors
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                          << infoLog << std::endl;
            }
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            glUseProgram(shaderProgram);

            glm::mat4 projection = glm::mat4(1.0f);

            projection = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, -1000.0f, 1000.0f);

            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        };

        ~RenderSystem() = default;

        template<typename Settings>
        void update(Manager<Settings>* manager) {
            for (int i = 0; i < m_registered_entities.size(); i++) {
                auto entity = m_registered_entities[i];
                TransformComponent &transform = manager->template get_component<TransformComponent>(entity);
                MeshComponent &mesh = manager->template get_component<MeshComponent>(entity);

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, transform.position);
                model = glm::scale(model, transform.scale);
                model = glm::rotate(model, glm::radians(transform.rotation.z), {0, 0, 1});

                glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
                glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, &color[0]);
                glBindVertexArray(mesh.VAO);
                glDrawElements(GL_TRIANGLES, 90, GL_UNSIGNED_INT, nullptr);
            }
        }

    private:
        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint shaderProgram;
        glm::vec3 color;

        const char *vertexSource = R"glsl(
            #version 330 core
            layout(location = 0) in vec3 position;

            uniform mat4 projection;
            uniform mat4 model;

            void main()
            {
                gl_Position = projection * model * vec4(position, 1.0);
            }
        )glsl";

        const char *fragmentSource = R"glsl(
            #version 330 core
            uniform vec3 color;

            out vec4 outColor;

            void main()
            {
                outColor = vec4(color, 1.0);
            }
        )glsl";
    };

} // namespace ecs

#endif
