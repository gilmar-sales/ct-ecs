project(SPACE)

file(GLOB_RECURSE SPACE_SRC
    "*.cpp"
    "*.hpp"
)

add_executable(space 
    ${SPACE_SRC}
)
target_link_libraries(space
    ct-ecs
    glad
    glfw
)

target_include_directories(space
	PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)