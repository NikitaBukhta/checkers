#--------------------------- MAIN CONFIGURATION ---------------------------#

cmake_minimum_required(VERSION 3.6.0)

project(checkers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_CXX_FLAGS_DEBUG  "-g")

set(
    MAIN_SRC
    main.cpp
)

add_executable(
    $CACHE{CMAKE_PROJECT_NAME}
    ${MAIN_SRC}
)

#----------------------------- LINK LIBRARIES -----------------------------#

add_subdirectory(game)
#add_subdirectory(exceptions)

set(
    ALL_LIBS
    $CACHE{GAME_CHECKERS_LINKER}
)

target_link_libraries(
    $CACHE{CMAKE_PROJECT_NAME}
    ${ALL_LIBS}
)