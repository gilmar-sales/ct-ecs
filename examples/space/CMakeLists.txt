project(SPACE)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SPACE_SRC
    "*.cpp"
)

add_executable(space 
    ${SPACE_SRC}
)

target_link_libraries(space
    ct-ecs
    glad
    glfw
    glm
)

target_include_directories(space
	PUBLIC
        $<INSTALL_INTERFACE:src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_precompile_headers(space
    PRIVATE 
    <iostream>
    <vector>
    <string>
    <tuple>
    <glad/glad.h>
    <GLFW/glfw3.h>
    <glm/glm.hpp>
)