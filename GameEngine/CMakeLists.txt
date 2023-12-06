cmake_minimum_required(VERSION 3.16)
project(samurai_ecs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add_library(${CMAKE_PROJECT_NAME} SHARED
#     src/your_library_source_file.cpp
# )

add_executable(${CMAKE_PROJECT_NAME}
    src/Damage.cpp
    src/EntitiesManager.cpp
    src/Gravity.cpp
    src/HealthPoint.cpp
    src/HitBox.cpp
    src/ID.cpp
    src/main.cpp
    src/Position.cpp
    src/Shooter.cpp
    src/Size.cpp
    src/Speed.cpp
    src/Systems.cpp
    src/Velocity.cpp
    )
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE)
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)


install(TARGETS ${CMAKE_PROJECT_NAME})
