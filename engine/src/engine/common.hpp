#pragma once
#include<cstdint>

namespace sb {

constexpr uint8_t MIN = 0;
constexpr uint8_t MAX = 255;
constexpr uint8_t DEPTH = 3;

enum PieceNoColor {
    Pawn    = 0b001,
    Bishop  = 0b010,
    Knight  = 0b011,
    Rook    = 0b100,
    Queen   = 0b101,
    King    = 0b110,
};

enum Piece {
    None    = 0b0000,
    BPawn   = 0b0001,
    WPawn   = 0b1001,
    BBishop = 0b0010,
    WBishop = 0b1010,
    BKnight = 0b0011,
    WKnight = 0b1011,
    BRook   = 0b0100,
    WRook   = 0b1100,
    BQueen  = 0b0101,
    WQueen  = 0b1101,
    BKing   = 0b0110,
    WKing   = 0b1110,
};

enum Castle {
    K = 1 << 0, // 1
    k = 1 << 1, // 2
    Q = 1 << 2, // 4
    q = 1 << 3, // 8
};

enum MoveInfo {
    OccupiedSquare,
    FreeSquare,
    Capture,
    Check,
};

} //namespace sb
