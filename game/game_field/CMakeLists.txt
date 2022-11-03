#----------------------------- CREATE LIBRARY -----------------------------#

cmake_minimum_required(VERSION 3.6.0)

set(
    LIB_NAME
    game_field_lib
)

set(
    SRC
    src/game_checkers.cpp
    src/checker.cpp
    src/ifigure.cpp
    src/game_field.cpp
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
    exceptions_lib
    players_lib
    config_lib
)

target_link_libraries(
    ${LIB_NAME}
    ${ALL_LIBS}
)