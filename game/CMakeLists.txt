#----------------------------- CREATE LIBRARY -----------------------------#

cmake_minimum_required(VERSION 3.19.0)

set(
    LIB_NAME
    config_lib
)

set(
    SRC
    config.hpp
)

add_library(
    ${LIB_NAME}
    INTERFACE
    ${SRC}
)

target_include_directories(
    ${LIB_NAME}
    INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#-------------------------- CREATE CACHE VARIABLE --------------------------#

add_subdirectory(exceptions)
add_subdirectory(player)
add_subdirectory(game_field)

# set cached variable to link all libs;
set(
    GAME_CHECKERS_LINKER
    exceptions_lib;
    game_field_lib;
    players_lib;
    config_lib;
    CACHE INTERNAL 
    "GAME_CHECKERS_LINKER"
)