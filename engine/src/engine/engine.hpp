#pragma once
#include<string>
#include"game.hpp"

namespace sb {

class Engine {
public:
    Engine(const std::string& p_fen);
    std::pair<std::string, std::string> get_best_move();

private:
    void generate_games(Game p_game);
    uint8_t evaluate_position(Game p_game);

    Game m_game;
};

} // namespace sb
