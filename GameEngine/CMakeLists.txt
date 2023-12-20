################# CMAKE #################
cmake_minimum_required(VERSION 3.16)
project(samurai_ecs)

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
    ecs_format
    COMMAND ${CLANG_FORMAT} -i ${FORMAT_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)




################# EXECUTABLE #################
add_library(${PROJECT_NAME} SHARED
    # src/EntitiesManager.cpp
    src/Damage.cpp
    src/Gravity.cpp
    src/HealthPoint.cpp
    src/HitBox.cpp
    src/ID.cpp
    src/main.cpp
    src/Shooter.cpp
    src/Size.cpp
    src/Speed.cpp
    src/Systems.cpp
)




################# LIBRARIES #################
target_link_libraries(${PROJECT_NAME} PRIVATE pthread dl sfml-window sfml-graphics sfml-system sfml-audio sfml-network)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)




################# INSTALL #################
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_dependencies(${PROJECT_NAME} server_format)
