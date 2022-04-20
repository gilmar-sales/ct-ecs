#ifndef SPACE_ECS_RENDER_SYSTEM_HPP
#define SPACE_ECS_RENDER_SYSTEM_HPP

#include <iostream>
#include <tuple>

#include <ecs/ecs.hpp>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../components/transform_component.hpp"
#include "../components/sprite_component.hpp"

#include "../shaders.h"

constexpr float SPRITE_SIZE = 32.0f;

namespace ecs {
    class RenderSystem : public BaseSystem<RenderSystem> {
    public:
        using Signature = std::tuple<ecs::TransformComponent, ecs::SpriteComponent>;

        RenderSystem(): color(1.0f, 1.0f, 1.0f) {
            // Initialize Sprite Quad Mesh
            float vertices[] = {
                    // positions          // colors           // texture coords (note that we changed them to 2.0f!)
                    0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
                    0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
                    -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
                    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left
            };

            unsigned int indices[] = {  // note that we start from 0!
                    0, 1, 3,   // first triangle
                    1, 2, 3    // second triangle
            };

            glGenVertexArrays(1, &sprite_vao);
            glBindVertexArray(sprite_vao);

            glGenBuffers(1, &sprite_vbo);

            glBindBuffer(GL_ARRAY_BUFFER, sprite_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glGenBuffers(1, &sprite_ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite_ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);

            // Initialize shaders
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexSource, nullptr);
            glCompileShader(vertexShader);
            checkShader(vertexShader)

            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
            glCompileShader(fragmentShader);
            checkShader(fragmentShader)

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

        ~RenderSystem() {
            glDeleteBuffers(1, &sprite_ebo);
            glDeleteBuffers(1, &sprite_vbo);
            glDeleteVertexArrays(1, &sprite_vao);
            glDeleteProgram(shaderProgram);
        };

        template<typename Settings>
        void update(Manager<Settings>* manager) {
            update_projection();
            for (unsigned int entity : m_registered_entities) {
                TransformComponent &transform = manager->template get_component<TransformComponent>(entity);
                SpriteComponent &sprite = manager->template get_component<SpriteComponent>(entity);

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, transform.position);
                model = glm::scale(model, transform.scale * SPRITE_SIZE);
                model = glm::rotate(model, glm::radians(transform.rotation.z), {0, 0, 1});

                glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
                glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, &color[0]);
                glBindVertexArray(sprite_vao);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, sprite.textures[0]);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            }

            glBindVertexArray(0);
        }

    private:
        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint shaderProgram;
        GLuint sprite_vao;
        GLuint sprite_vbo;
        GLuint sprite_ebo;
        glm::vec3 color;

        void update_projection();

        const char *vertexSource = R"glsl(
            #version 330 core
            layout(location = 0) in vec3 position;
            layout (location = 1) in vec3 color;
            layout (location = 2) in vec2 texture_coord;

            uniform mat4 projection;
            uniform mat4 model;

            out vec3 Color;
            out vec2 TexCoord;

            void main()
            {
                gl_Position = projection * model * vec4(position, 1.0);
                Color = color;
                TexCoord = texture_coord;
            }
        )glsl";

        const char *fragmentSource = R"glsl(
            #version 330 core
            uniform sampler2D Texture;

            in vec3 Color;
            in vec2 TexCoord;

            out vec4 outColor;

            void main()
            {
                vec4 texColor = texture(Texture, TexCoord);

                if(texColor.a < 0.1)
                    discard;

                outColor = texColor * vec4(Color, 1.0);
            }
        )glsl";
    };

} // namespace ecs

#endif
