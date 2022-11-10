#----------------------------- CREATE LIBRARY -----------------------------#

cmake_minimum_required(VERSION 3.0.0)

set(
    LIB_NAME
    exceptions_lib
)

set(
    SRC
    src/unright_color_exception.cpp
    src/wrong_checker_move_exception.cpp
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