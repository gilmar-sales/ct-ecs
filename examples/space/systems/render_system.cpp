#include "render_system.hpp"

#include "../core/application.hpp"

namespace ecs {
        void RenderSystem::update_projection() {
            float half_width = Application::get().get_window().get_window_width() / 2;
            float half_height = Application::get().get_window().get_window_height() / 2;
            glm::mat4 projection = glm::mat4(1.0f);

            projection = glm::ortho(-half_width, half_width, -half_height, half_height, -1000.0f, 1000.0f);

            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        }
}