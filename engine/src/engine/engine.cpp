#include"engine.hpp"
#include"common.hpp"
#include"game.hpp"
#include<vector>

namespace sb {

Engine::Engine(const std::string& p_fen) 
    : m_game(p_fen){}

std::pair<std::string, std::string> Engine::get_move() {

    minimax(m_game, MIN, MAX, 0);

    return {"",""};
}

int Engine::minimax(Game& p_game, uint8_t p_a, uint8_t p_b, int p_depth) {
    if(p_depth == 1) return p_game.get_eval();
    std::vector<Game> games = gen_moves(p_game);

    return 0;
}

std::vector<Game> Engine::gen_moves(Game& p_game) {
    std::vector<Game> games;

        
    
    #ifndef NDEBUG
    for(auto& n : games)
        n.print_debug();
    #endif
    return games;
}

void Engine::gen_pawn_moves(std::vector<Game>& p_games, Game& p_game, const square& sqr) {
    // 4 squares to check max
}

void Engine::gen_knight_moves(std::vector<Game>& p_games, Game& p_game, const square& sqr) {
    // 8 squares to check max
}

void Engine::gen_bishop_moves(std::vector<Game>& p_games, Game& p_game, const square& sqr) {
    // diagonals
}

void Engine::gen_rook_moves(std::vector<Game>& p_games, Game& p_game, const square& sqr) {
    // cardinals
}

void Engine::gen_queen_moves(std::vector<Game>& p_games, Game& p_game, const square& sqr) {
    // diagonals and cardinals
}

void Engine::gen_king_moves(std::vector<Game>& p_games, Game& p_game, const square& sqr) {
    // 8 moves around and castle
}

uint8_t Engine::evaluate_position(const Game& p_game) {
    
    return 0;
}

} //namespace sb
