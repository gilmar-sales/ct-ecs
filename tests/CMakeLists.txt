project(Test)

add_subdirectory(dependencies/googletest)

enable_testing()
include(GoogleTest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB_RECURSE TESTS_SRC
        "src/*.cpp"
        )

add_executable(Tests_run ${TESTS_SRC})

target_compile_definitions(Tests_run PUBLIC -DCT_ECS_BUILDING_TESTS)

target_link_libraries(Tests_run gtest gtest_main gmock ct-ecs glm)
target_include_directories(Tests_run PUBLIC ${gtest_SOURCE_DIR}/include)
gtest_discover_tests(Tests_run)
