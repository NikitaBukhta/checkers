#include "game_checkers.hpp"
#include "logger.hpp"

using namespace std::literals;

int main(int argc, char **argv){
    Logger::set_file_name("checkers");
    Logger::turn_output_logs_to_console(false);
    Logger::do_log("Program has been started", Logger::Level::INFO);

    game::GameCheckers game;

    return game.start();
}