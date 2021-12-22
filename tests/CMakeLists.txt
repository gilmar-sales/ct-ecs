project(Test)

add_subdirectory(dependencies/googletest)

include(CTest)
include(GoogleTest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB_RECURSE TESTS_SRC
        "src/*.cpp"
        )

add_executable(Tests_run ${TESTS_SRC})
target_link_libraries(Tests_run gtest gtest_main ct-ecs glm)
target_include_directories(Tests_run PUBLIC ${gtest_SOURCE_DIR}/include)
gtest_discover_tests(Tests_run)
