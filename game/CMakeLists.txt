add_subdirectory(exceptions)
add_subdirectory(game_field)

set(
    GAME_CHECKERS_LINKER
    "checkers_lib;
    exceptions_lib"
    CACHE FILEPATH 
    ""
)