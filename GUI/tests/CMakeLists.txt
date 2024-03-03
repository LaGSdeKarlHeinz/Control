# CMakeLists.txt in tests/ directory

find_package(GTest REQUIRED)

# Add the test executable
add_executable(my_tests my_test.cpp)

# Link against Google Test and any other necessary libraries
target_link_libraries(my_tests PRIVATE GTest::GTest GTest::Main)

# Optionally, you can add a test target for running the tests conveniently
add_custom_target(run_tests COMMAND my_tests DEPENDS my_tests)
