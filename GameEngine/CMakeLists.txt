cmake_minimum_required(VERSION 3.16)
project(samurai_ecs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create a library for EntitiesManager
add_library(EntitiesManager
    src/EntitiesManager.cpp
)

# Define the target for your executable
add_executable(${CMAKE_PROJECT_NAME}
    src/Damage.cpp
    src/Gravity.cpp
    src/HealthPoint.cpp
    src/HitBox.cpp
    src/ID.cpp
    src/main.cpp
    # src/Position.cpp
    src/Shooter.cpp
    src/Size.cpp
    src/Speed.cpp
    src/Systems.cpp
    # src/Velocity.cpp
)

# Link the EntitiesManager library to the executable
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE EntitiesManager)

# Set include directories
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)
target_include_directories(EntitiesManager PRIVATE include)

# Set C++ standard
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_features(EntitiesManager PRIVATE cxx_std_20)

# Install targets
install(TARGETS ${CMAKE_PROJECT_NAME} EntitiesManager)

