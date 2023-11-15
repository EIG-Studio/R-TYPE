cmake_minimum_required(VERSION 3.16)
project(R-TYPE LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML 2.5 COMPONENTS window graphics system REQUIRED)

add_executable(R-TYPE src/main.cpp)
target_link_libraries(R-TYPE PRIVATE sfml-window sfml-graphics sfml-system)

install(TARGETS R-TYPE)
