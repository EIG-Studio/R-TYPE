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

find_package(Boost REQUIRED)
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
    src/client.cpp
    src/game.cpp
)

################# LIBRARIES #################

target_include_directories(${PROJECT_NAME} PRIVATE include ../GameEngine/include ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-window sfml-graphics sfml-system sfml-audio sfml-network Boost::boost samurai_ecs)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if (NOT WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC pthread dl)
endif()

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
    add_custom_command(
            TARGET ${PROJECT_NAME}
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM)
endif()


################# INSTALL #################
install(TARGETS ${PROJECT_NAME})
add_dependencies(${PROJECT_NAME} server_format)
