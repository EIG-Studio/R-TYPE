cmake_minimum_required(VERSION 3.16)
project(samurai_server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME}
    src/main.cpp
    )
target_include_directories(${PROJECT_NAME} PRIVATE include)
# target_link_libraries(${PROJECT_NAME} PRIVATE)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)


install(TARGETS ${PROJECT_NAME})
