################# CMAKE #################
cmake_minimum_required(VERSION 3.16)
project(samurai_server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



################# FETCH #################
include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)

FetchContent_MakeAvailable(SFML)

################# CLANG-FORMAT #################
find_program(CLANG_FORMAT "clang-format")

set(FORMAT_SOURCE_FILES
    src/*.cpp
    include/*.hpp
)

add_custom_target(
    server_format
    COMMAND ${CLANG_FORMAT} -i ${FORMAT_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)



################# EXECUTABLE #################
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/server.cpp
    src/command.cpp
)



################# LIBRARIES #################
target_include_directories(${PROJECT_NAME} PRIVATE include ../GameEngine/include)
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-window sfml-graphics sfml-system sfml-audio sfml-network pthread dl samurai_ecs)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)



################# INSTALL #################
install(TARGETS ${PROJECT_NAME})
add_dependencies(${PROJECT_NAME} server_format)
