#pragma once
#include<string>

/* Uses bit magic to represent the chess board as 
 * each row is a uint32_t that contains 1 color bit, 3 id bits * 8
 * for each square
 * this cuts the space in half from a char array
 */ 

namespace sb {

enum Piece {
    None,   // 000
    Pawn,   // 001
    Bishop, // 010
    Knight, // 011
    Rook,   // 100
    Queen,  // 101
    King,   // 110
};

enum Castle {
    K = 1 << 0, // 1
    k = 1 << 1, // 2
    Q = 1 << 2, // 4
    q = 1 << 3, // 8
};

class Game {
public:
    // Constructor for server interface
    Game(const std::string& p_fen);

    // Setters //

    void set_pieces(uint32_t p_pieces[8]);
    void set_turn(char p_turn);
    void set_castle(uint8_t p_castle);
    void set_en_passant(int8_t p_en_passant);

    void set_eval(uint8_t p_eval);

    // Getters //

    const uint32_t* get_pieces();
    const char get_turn();
    const uint8_t get_castle();
    const int8_t get_en_passant();

    const uint8_t get_eval();
private:
    // Private Member Functions //

    void decode_fen(const std::string& p_fen) noexcept; // assumes serverside fen checks may change in future

    // Private Member Variables //

    uint32_t m_pieces[8]{};    // [1bit color, 3bit piece]
    char m_turn{ 0 };          // 'w' or 'b'
    uint8_t m_castle{ 0 };     // used with Castle enum
    int8_t m_en_passant{ -1 }; // en passant square

    uint8_t m_eval{ 0x7f };    // 0-255, starts at 127 and +/- based on position
};

} // namespace sb
