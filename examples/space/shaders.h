#pragma once

#define checkShader(shader)                                 \
{                                                           \
    GLint status;                                           \
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);      \
                                                            \
    if(status == -1) {                                      \
        char buffer[512];                                   \
        glGetShaderInfoLog(shader, 512, NULL, buffer);      \
                                                            \
        std::cout << buffer << std::endl;                   \
    } else {                                                \
        std::cout << #shader << " compiled successfuly!\n"; \
    }                                                       \
                                                            \
}
