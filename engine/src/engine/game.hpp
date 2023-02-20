#pragma once
#include<common.hpp>
#include<cstdint>
#include<string>

/* Uses bit magic to represent the chess board
 * each row is a uint32_t that contains [ 1 color bit, 3 id bits ] * 8
 * for each square
 * this cuts the space in half from a char array
 */ 

namespace sb {

struct square {
    size_t x;
    size_t y;
    square(size_t p_x, size_t p_y)
        : x(p_x), y(p_y) {}
};

class Game {
public:
    Game(const std::string p_fen);

    // Setters //
    void move(const square& p_src, const square& p_dst);
    void promote(const square& p_sqr, Piece p_piece);
    void capture(const square& p_src, const square& p_dst);
    void castle(Castle p_castle);

    void set_turn(char p_turn) { this->m_turn = p_turn; }
    void set_eval(uint8_t p_eval) { this->m_eval = p_eval; }
    void remove_castle(uint8_t p_castle) { this->m_castle &= ~p_castle; }

    // Getters //
    Piece get_square(const square& p_sqr);

    const char get_turn() { return this->m_turn; }
    const uint8_t get_eval() { return this->m_eval; }
    const uint8_t get_castle() { return this->m_castle; }

    // Public Functions //
    MoveInfo check_move(const square& p_src, const square& p_dst);

    // Debug Functions //
    #ifndef DNEBUG
    void print_debug();
    #endif // NDEBUG

private:
    // Private Member Functions //
    void decode_fen(const std::string& p_fen) noexcept; // assumes serverside fen checks may change in future

    // Private Member Variables //
    uint32_t m_pieces[8]{};    // [1bit color, 3bit piece]
    char m_turn{ 0 };          // 'w' or 'b'
    uint8_t m_castle{ 0 };     // used with Castle enum
    int8_t m_en_passant{ -1 }; // en passant square

    uint8_t m_eval{ 0x7f };    // 0-255, starts at 127 and +/- based on position
                               
    friend class Fen;          // helper for fen decoding
};

} // namespace sb
