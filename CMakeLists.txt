project(CT-ECS)

file(GLOB_RECURSE ECS_SRC
    "src/*.cpp"
    "src/*.hpp"
)

add_library(ct-ecs 
    ${ECS_SRC}
)

target_include_directories(ct-ecs INTERFACE
	PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(examples)