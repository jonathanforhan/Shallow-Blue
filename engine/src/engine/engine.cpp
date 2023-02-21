#include"engine.hpp"
#include"common.hpp"
#include"game.hpp"
#include<string>
#include<vector>
#include<iostream>

namespace sb {

Engine::Engine(const std::string& p_fen) 
    : m_game(p_fen){}

std::string Engine::get_move() {

    std::vector<Game> g = gen_moves(m_game);

    std::pair<uint8_t, size_t> best = {0, 0};

    for(size_t i = 0; i < g.size(); i++) {
        int s = minimax(g[i], MIN, MAX, 0);
        if(s > best.first) {
            best = { s, i };
            std::cout << s << '\n';
        }
    }

    std::string from = "";
    std::string to = "";

    for(size_t i = 0; i < 8; i++) {
        for(size_t j = 0; j < 8; j++) {
            if(m_game.get_square({ j, i }) != g[best.second].get_square({ j, i })) {
                if(g[best.second].get_square({ j, i }) != Piece::None) {
                    from += (char)(j + 97);
                    from += (char)(i + '1');
                } else {
                    to += (char)(j + 97);
                    to += (char)(i + '1');
                }
            }
        }
    }

    std::string res = from + "-" + to;

    std::cout << "from: " << from << " to: " << to << '\n';

    g[best.second].print_debug();

    return res;
}

int Engine::minimax(Game& p_game, uint8_t p_a, uint8_t p_b, int p_depth) {
    if(p_depth == DEPTH) return p_game.get_eval();
    std::vector<Game> games = gen_moves(p_game);

    for(auto& game : games) {
        int wp = 0;
        int bp = 0;
        for(size_t i = 0; i < 8; i++) {
            for(size_t j = 0; j < 8; j++) {
                Piece p = game.get_square({ j, i });
                if((p >> 3) & 1) { // if white
                    if(p == Piece::WKing) wp += 50;
                    else if(p == Piece::WQueen) wp += 9;
                    else if(p == Piece::WRook) wp += 5;
                    else if(p == Piece::WKnight) wp += 3;
                    else if(p == Piece::WBishop) wp += 3;
                    else if(p == Piece::WPawn) wp += 1;
                } else {
                    if(p == Piece::BKing) bp += 50;
                    else if(p == Piece::BQueen) bp += 9;
                    else if(p == Piece::BRook) bp += 5;
                    else if(p == Piece::BKnight) bp += 3;
                    else if(p == Piece::BBishop) bp += 3;
                    else if(p == Piece::BPawn) bp += 1;
                }
            } // end j loop
        } // end i loop
        if(game.get_turn() == 'w') {
            uint8_t eval = (127 + (wp - bp));
            if(game.get_eval() < eval - 3) {
                return eval;
            }
            game.set_eval(eval);
            game.set_turn('b');
            p_game.set_eval(256 - minimax(game, p_a, p_b, p_depth+1));
        } else {
            uint8_t eval = (127 + (bp - wp));
            if(game.get_eval() < eval - 3) {
                return eval;
            }
            game.set_eval(eval);
            game.set_turn('w');
            p_game.set_eval(256 - minimax(game, p_a, p_b, p_depth+1));
        }
    } // end auto loop
    return p_game.get_eval();
}

std::vector<Game> Engine::gen_moves(Game& p_game) {
    std::vector<Game> games;

    for(size_t i = 0; i < 8; i++) {
        for(size_t j = 0; j < 8; j++) {
            Piece p = p_game.get_square({ j, i });
            if(p_game.get_turn() == 'w') {
                switch(p) {
                    case Piece::WPawn:
                        gen_pawn_moves(games, p_game, { j, i });
                        break;
                    case Piece::WBishop:
                        gen_bishop_moves(games, p_game, { j, i });
                        break;
                    case Piece::WKnight:
                        gen_knight_moves(games, p_game, { j, i });
                        break;
                    case Piece::WRook:
                        gen_rook_moves(games, p_game, { j, i });
                        break;
                    case Piece::WQueen:
                        gen_queen_moves(games, p_game, { j, i });
                        break;
                    case Piece::WKing:
                        gen_king_moves(games, p_game, { j, i });
                        break;
                    default: break;
                }
            } else {
                switch(p) {
                    case Piece::BPawn:
                        gen_pawn_moves(games, p_game, { j, i });
                        break;
                    case Piece::BBishop:
                        gen_bishop_moves(games, p_game, { j, i });
                        break;
                    case Piece::BKnight:
                        gen_knight_moves(games, p_game, { j, i });
                        break;
                    case Piece::BRook:
                        gen_rook_moves(games, p_game, { j, i });
                        break;
                    case Piece::BQueen:
                        gen_queen_moves(games, p_game, { j, i });
                        break;
                    case Piece::BKing:
                        gen_king_moves(games, p_game, { j, i });
                        break;
                    default: break;
                }
            }
        }
    }
    
    #ifndef NDEBUG
    //for(auto& n : games)
        //n.print_debug();
    //std::cout << "\nSize: " << games.size() << '\n';
    #endif
    return games;
}

bool Engine::handle_gen_move(std::vector<Game>& p_games, Game& p_game, const square& p_sqr, const square& p_dst) {
    // guard statement works becase of unsigned overflow
    if(p_dst.x > 7 || p_dst.y > 7) return false;

    MoveInfo mi = p_game.check_move(p_sqr, p_dst);
    Game new_game = p_game;

    if(mi == MoveInfo::FreeSquare) {
        new_game.move(p_sqr, p_dst);
    } else if(mi == MoveInfo::Capture) {
        new_game.capture(p_sqr, p_dst);
    } else {
        return false;
    }

    p_games.push_back(new_game);
    return true;
}

void Engine::gen_pawn_moves(std::vector<Game>& p_games, Game& p_game, const square& p_sqr) {
    const auto handle_pawn_attack = [&](square _dst) {
        if(_dst.x > 7 || _dst.y > 7) return;

        MoveInfo mi = p_game.check_move(p_sqr, _dst);
        Game new_game = p_game;

        if(mi == MoveInfo::Capture) {
            new_game.capture(p_sqr, _dst);
            p_games.push_back(new_game);
        }
    };
    if(p_game.get_turn() == 'w') {
        if(handle_gen_move(p_games, p_game, p_sqr, { p_sqr.x, p_sqr.y + 1 })) {
            if(p_sqr.y == 1) {
                handle_gen_move(p_games, p_game, p_sqr, { p_sqr.x, p_sqr.y + 2 });
            }
        }
        handle_pawn_attack({ p_sqr.x + 1, p_sqr.y + 1 });
        handle_pawn_attack({ p_sqr.x - 1, p_sqr.y + 1 });
    } else {
        if(handle_gen_move(p_games, p_game, p_sqr, { p_sqr.x, p_sqr.y - 1 })) {
            if(p_sqr.y == 6) {
                handle_gen_move(p_games, p_game, p_sqr, { p_sqr.x, p_sqr.y - 2 });
            }
        }
        handle_pawn_attack({ p_sqr.x + 1, p_sqr.y - 1 });
        handle_pawn_attack({ p_sqr.x - 1, p_sqr.y - 1 });
    }
}

void Engine::gen_knight_moves(std::vector<Game>& p_games, Game& p_game, const square& p_sqr) {
    std::vector<square> mvs = {
        { p_sqr.x + 1, p_sqr.y + 2 }, { p_sqr.x + 2, p_sqr.y + 1 },
        { p_sqr.x - 1, p_sqr.y + 2 }, { p_sqr.x + 2, p_sqr.y - 1 },
        { p_sqr.x + 1, p_sqr.y - 2 }, { p_sqr.x - 2, p_sqr.y + 1 },
        { p_sqr.x - 1, p_sqr.y - 2 }, { p_sqr.x - 2, p_sqr.y - 1 },
    };
    for(auto& mv : mvs) {
        handle_gen_move(p_games, p_game, p_sqr, mv);
    }
}

void Engine::gen_bishop_moves(std::vector<Game>& p_games, Game& p_game, const square& p_sqr) {
    square dst = p_sqr;
    while(handle_gen_move(p_games, p_game, p_sqr, { ++dst.x, ++dst.y })){} dst = p_sqr;
    while(handle_gen_move(p_games, p_game, p_sqr, { ++dst.x, --dst.y })){} dst = p_sqr;
    while(handle_gen_move(p_games, p_game, p_sqr, { --dst.x, ++dst.y })){} dst = p_sqr;
    while(handle_gen_move(p_games, p_game, p_sqr, { --dst.x, --dst.y })){}
}

void Engine::gen_rook_moves(std::vector<Game>& p_games, Game& p_game, const square& p_sqr) { 
    square dst = p_sqr;
    while(handle_gen_move(p_games, p_game, p_sqr, { ++dst.x, dst.y })){} dst = p_sqr;
    while(handle_gen_move(p_games, p_game, p_sqr, { dst.x, ++dst.y })){} dst = p_sqr;
    while(handle_gen_move(p_games, p_game, p_sqr, { --dst.x, dst.y })){} dst = p_sqr;
    while(handle_gen_move(p_games, p_game, p_sqr, { dst.x, --dst.y })){}
}

void Engine::gen_queen_moves(std::vector<Game>& p_games, Game& p_game, const square& p_sqr) { 
    square dst = p_sqr;
    while(handle_gen_move(p_games, p_game, p_sqr, { ++dst.x, dst.y })){} dst = p_sqr;
    while(handle_gen_move(p_games, p_game, p_sqr, { dst.x, ++dst.y })){} dst = p_sqr;
    while(handle_gen_move(p_games, p_game, p_sqr, { --dst.x, dst.y })){} dst = p_sqr;
    while(handle_gen_move(p_games, p_game, p_sqr, { dst.x, --dst.y })){} dst = p_sqr;

    while(handle_gen_move(p_games, p_game, p_sqr, { ++dst.x, ++dst.y })){} dst = p_sqr;
    while(handle_gen_move(p_games, p_game, p_sqr, { ++dst.x, --dst.y })){} dst = p_sqr;
    while(handle_gen_move(p_games, p_game, p_sqr, { --dst.x, ++dst.y })){} dst = p_sqr;
    while(handle_gen_move(p_games, p_game, p_sqr, { --dst.x, --dst.y })){}
}

void Engine::gen_king_moves(std::vector<Game>& p_games, Game& p_game, const square& p_sqr) { // 8 moves around and castle
    handle_gen_move(p_games, p_game, p_sqr, { p_sqr.x + 1, p_sqr.y });
    handle_gen_move(p_games, p_game, p_sqr, { p_sqr.x - 1, p_sqr.y });
    handle_gen_move(p_games, p_game, p_sqr, { p_sqr.x, p_sqr.y + 1 });
    handle_gen_move(p_games, p_game, p_sqr, { p_sqr.x, p_sqr.y - 1 });

    handle_gen_move(p_games, p_game, p_sqr, { p_sqr.x + 1, p_sqr.y + 1 });
    handle_gen_move(p_games, p_game, p_sqr, { p_sqr.x - 1, p_sqr.y + 1 });
    handle_gen_move(p_games, p_game, p_sqr, { p_sqr.x + 1, p_sqr.y - 1 });
    handle_gen_move(p_games, p_game, p_sqr, { p_sqr.x - 1, p_sqr.y - 1 });
}

} //namespace sb
