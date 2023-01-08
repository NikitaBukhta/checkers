#include "game_checkers.hpp"
#include "logger.hpp"

#include <thread>

int main(int argc, char **argv){
    std::thread log_file_name_th(&Logger::set_file_name, "checkers");
    std::thread log_turn_off_console_th (&Logger::turn_output_logs_to_console, false);
    std::thread log_set_min_lvl_th (&Logger::set_min_lvl, Logger::Level::DEBUG);

    log_file_name_th.join();
    log_turn_off_console_th.join();
    log_set_min_lvl_th.join();

    std::thread(&Logger::do_log, "Program has been started", Logger::Level::INFO).detach();

    game::GameCheckers game;

    return game.start();
}