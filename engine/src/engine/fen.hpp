#pragma once
#include"game.hpp"
#include"common.hpp"
#include<cstdint>
#include<string>

namespace sb {

// GAME FRIEND CLASS
class Fen {
public:
    static void decode(Game* p_game, const std::string& p_fen);
};

} // namespace sb
