################# CMAKE #################
cmake_minimum_required(VERSION 3.16)
project(samurai_client)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



################# FETCH #################
include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)

FetchContent_MakeAvailable(SFML)

################# CLANG FORMAT #################
find_program(CLANG_FORMAT "clang-format")

set(FORMAT_SOURCE_FILES
    src/*.cpp
    include/*.hpp
)

add_custom_target(
    client_format
    COMMAND ${CLANG_FORMAT} -i ${FORMAT_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(Boost REQUIRED)
################# EXECUTABLE #################
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/menu/introMenu/introMenu.cpp
    src/menu/settingMenu.cpp
    src/sprite/sprite.cpp
    src/music/music.cpp
    src/menu/inGame.cpp
    src/commandsToServer.cpp
)



################# LIBRARIES #################
target_include_directories(${PROJECT_NAME} PRIVATE include ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-window sfml-graphics sfml-system sfml-audio sfml-network Boost::boost)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if (NOT WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC pthread dl)
endif()


################# INSTALL #################
install(TARGETS ${PROJECT_NAME})
add_dependencies(${PROJECT_NAME} client_format)
