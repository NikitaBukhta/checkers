#----------------------------- CREATE LIBRARY -----------------------------#

cmake_minimum_required(VERSION 3.6.0)

set(
    LIB_NAME
    players_lib
)

set(
    SRC
    src/player.cpp
    src/player_info.cpp
)

add_library(
    ${LIB_NAME}
    ${SRC}
)

target_include_directories(
    ${LIB_NAME}
    PUBLIC
    include
)

#----------------------------- LINK LIBRARIES -----------------------------#

set(
    ALL_LIBS
    game_field_lib
    config_lib
)

target_link_libraries(
    ${LIB_NAME}
    ${ALL_LIBS}
)