################# CMAKE #################
cmake_minimum_required(VERSION 3.16)
project(samurai)



################# set #################
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



################# subdirectory #################
add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(GameEngine)
