cmake_minimum_required(VERSION 3.16)
project(cursova LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Sql Widgets Charts)

qt_standard_project_setup()

add_subdirectory(src/app)
add_subdirectory(src/logic)
add_subdirectory(test)

target_include_directories(${PROJECT_NAME} PRIVATE
    src/app
    src/logic
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${PROJECT_NAME}_logic
)

