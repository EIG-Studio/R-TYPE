cmake_minimum_required(VERSION 3.16)
project(samurai)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp src/sprite.cpp src/music.cpp)
include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-window sfml-graphics sfml-system sfml-audio sfml-network)
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)


install(TARGETS ${CMAKE_PROJECT_NAME})
