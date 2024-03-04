# Add the test executable
add_executable(my_tests my_test.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Link against the Google Test libraries
target_link_libraries(
  my_tests
  GTest::gtest_main
)

# Optionally, you can add a test target for running the tests conveniently
add_custom_target(run_tests COMMAND my_tests DEPENDS my_tests)
