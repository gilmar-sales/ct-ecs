cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)

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

option(OPTION_BUILD_EXAMPLES "Build all examples." ON)

if(OPTION_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

option(CT_ECS_BUILD_TESTS "Build all tests." OFF)

if (CT_ECS_BUILD_TESTS)
add_subdirectory(tests)
endif()