cmake_minimum_required(VERSION 3.15)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
  gtest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(gtest)

add_executable(test_${PROJECT_NAME} test_logic.cpp)

target_link_libraries(test_${PROJECT_NAME} GTest::gtest_main GTest::gtest ${PROJECT_NAME}_logic)

target_include_directories(test_${PROJECT_NAME} PRIVATE
    ../src/logic
)

include(GoogleTest)
gtest_discover_tests(test_${PROJECT_NAME})