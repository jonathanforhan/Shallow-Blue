#pragma once
#include<cstdint>
#include<string>
#include<vector>
#include"game.hpp"
#include"common.hpp"

namespace sb {

class Engine {
public:
    Engine(const std::string& p_fen);
    std::string get_move();

private:
    int minimax(Game& p_game, uint8_t p_a, uint8_t p_b, int p_depth);
    std::vector<Game> gen_moves(Game& p_game);
    bool handle_gen_move(std::vector<Game>& p_games, Game& p_game, const square& p_sqr, const square& p_dst);
    void gen_pawn_moves(std::vector<Game>& p_games, Game& p_game, const square& p_sqr);
    void gen_knight_moves(std::vector<Game>& p_games, Game& p_game, const square& p_sqr);
    void gen_bishop_moves(std::vector<Game>& p_games, Game& p_game, const square& p_sqr);
    void gen_rook_moves(std::vector<Game>& p_games, Game& p_game, const square& p_sqr);
    void gen_queen_moves(std::vector<Game>& p_games, Game& p_game, const square& p_sqr);
    void gen_king_moves(std::vector<Game>& p_games, Game& p_game, const square& p_sqr);

    Game m_game;
    int size = 0;
};

} // namespace sb
