project(Test)

option(CT_ECS_BUILD_TESTS "Build all tests." OFF) # Makes boolean 'test' available.

if (CT_ECS_BUILD_TESTS)
        add_subdirectory(dependencies/googletest)

        include(CTest)

        include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

        file(GLOB_RECURSE TESTS_SRC
                "src/*.cpp"
                )

        add_executable(Tests_run ${TESTS_SRC})
        target_link_libraries(Tests_run gtest gtest_main ct-ecs glm)
        target_include_directories(Tests_run PUBLIC ${gtest_SOURCE_DIR}/include)

        add_test(tests Tests_run)
endif()