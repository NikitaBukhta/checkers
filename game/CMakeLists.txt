add_subdirectory(exceptions)
add_subdirectory(player)
add_subdirectory(game_field)

# set cached variable to link all libs;
set(
    GAME_CHECKERS_LINKER
    exceptions_lib;
    game_field_lib;
    players_lib;
    CACHE INTERNAL 
    "GAME_CHECKERS_LINKER"
)