#ifndef SPACE_MESH_ASSET_HPP
#define SPACE_MESH_ASSET_HPP

#include <vector>
#include <glad/glad.h>

class MeshAsset {
public:
    static unsigned get_circle_mesh(float radius = 10.0f) {
        static bool initialized = false;
        static unsigned VAO;

        if (!initialized) {
            std::vector<glm::vec3> vertices = std::vector<glm::vec3>(32);

            vertices[0] = {0, 0, 0};

            for (unsigned i = 1; i < 32; i++) {
                float angle = (360.f / 30.f) * (i - 1);
                glm::vec3 vertice = {glm::cos(glm::radians(angle)), glm::sin(glm::radians(angle)), 0};
                vertices[i] = vertice;
            }

            std::vector<unsigned> indices = std::vector<unsigned>(96);

            for (unsigned i = 0; i < 32; i++) {
                indices[0 + (i * 3)] = 0;
                indices[1 + (i * 3)] = i + 1;
                indices[2 + (i * 3)] = i + 2;
            }

            // indices[89] = 1;

            unsigned VBO, EBO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            initialized = true;
        }

        return VAO;
    }

    static unsigned get_triangle_mesh(float radius = 10.0f) {
        float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f};

        unsigned indices[] = {
                0,
                1,
                2,
        };

        unsigned VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return VAO;
    }

    static unsigned get_asteroid_mesh(float radius = 10.0f) {
        static bool initialized = false;
        static unsigned VAO;

        if (!initialized) {
            float vertices[] = {
                    -1.f,
                    -2.f,
                    0.0f,
                    -2.f,
                    -1.f,
                    0.0f,
                    -2.f,
                    0.0f,
                    0.0f,
                    -1.f,
                    1.0f,
                    0.0f,
                    0.0f,
                    0.5f,
                    0.0f,
                    1.0f,
                    1.0f,
                    0.0f,
                    1.8f,
                    0.0f,
                    0.0f,
                    1.2f,
                    -1.2f,
                    0.0f,
                    0.0f,
                    -2.0f,
                    0.0f,
            };

            unsigned indices[] = {
                    0,
                    1,
                    2,
                    0,
                    2,
                    3,
                    0,
                    3,
                    8,
                    3,
                    4,
                    8,
                    4,
                    7,
                    8,
                    4,
                    5,
                    7,
                    5,
                    7,
                    6,
            };

            unsigned VBO, EBO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            initialized = true;
        }

        return VAO;
    }
};

#endif // SPACE_MESH_ASSET_HPP
