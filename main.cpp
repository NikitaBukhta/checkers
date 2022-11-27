#include "game_checkers.hpp"
#include "logger.hpp"

using namespace std::literals;

int main(int argc, char **argv){
    Logger::set_file_name("checkers");
    Logger::turn_output_logs_to_console(false);
    Logger::set_min_lvl(Logger::Level::DEBUG);
    Logger::do_log("Program has been started", Logger::Level::INFO);

    game::GameCheckers game;

    return game.start();
}