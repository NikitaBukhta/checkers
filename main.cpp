#include "game_checkers.hpp"
#include "logger.hpp"

using namespace std::literals;

int main(int argc, char **argv){
    Logger::set_file_name("checkers");
    Logger::do_log("Program has been started");

    game::GameCheckers game;

    return game.start();
}