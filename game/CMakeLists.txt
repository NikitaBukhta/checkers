add_subdirectory(exceptions)
add_subdirectory(game_field)
add_subdirectory(player)

# set cached variable to link all libs;
set(
    GAME_CHECKERS_LINKER
    exceptions_lib;
    game_field_lib;
    players_lib;
    CACHE INTERNAL 
    "GAME_CHECKERS_LINKER"
)