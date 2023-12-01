################# CMAKE #################
cmake_minimum_required(VERSION 3.16)
project(samurai_server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



################# FETCH #################


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
)



################# LIBRARIES #################
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)



################# INSTALL #################
install(TARGETS ${PROJECT_NAME})
add_dependencies(${PROJECT_NAME} server_format)
