#include"game.hpp"
#include"common.hpp"
#include"fen.hpp"
#include<bitset>
#include<cstdint>
#include<stdexcept>
#include<iostream>
#include<utility>

namespace sb {

Game::Game(const std::string p_fen) {
    decode_fen(p_fen);
}

// Setters //

void Game::move(const square& p_src, const square& p_dst) {
    // non-capture move
    Piece piece = get_square(p_src);
    
    uint32_t* src_row = &m_pieces[p_src.y];
    uint32_t* dst_row = &m_pieces[p_dst.y];
    *src_row &= ~(0xf << p_src.x * 4); // clear bits intended to move
    *dst_row |= piece << (p_dst.x * 4);
}

void Game::promote(const square& p_sqr, Piece p_piece) {
    uint32_t* sqr_row = &m_pieces[p_sqr.y];
    *sqr_row &= ~(0xf << p_sqr.x * 4);    // clear bits
    *sqr_row |= p_piece << (p_sqr.x * 4); // promote
}

void Game::capture(const square& p_src, const square& p_dst) {
    Piece piece = get_square(p_src);
    
    uint32_t* src_row = &m_pieces[p_src.y];
    uint32_t* dst_row = &m_pieces[p_dst.y];
    *src_row &= ~(0xf << p_src.x * 4); // clear bits intended to move
    *dst_row &= ~(0xf << p_dst.x * 4); // clear bits of captured piece
    *dst_row |= piece << (p_dst.x * 4);
}

void Game::castle(Castle p_castle) {
    remove_castle(0xf); // clear castle rights
    switch(p_castle) {
        case Castle::K:
            move({ 4, 0 }, { 6, 0 });
            move({ 7, 0 }, { 5, 0 });
            break;
        case Castle::k:
            move({ 4, 7 }, { 6, 7 });
            move({ 7, 7 }, { 5, 7 });
            break;
        case Castle::Q:
            move({ 4, 0 }, { 2, 0 });
            move({ 0, 0 }, { 3, 0 });
            break;
        case Castle::q:
            move({ 4, 7 }, { 2, 7 });
            move({ 0, 7 }, { 3, 7 });
            break;
        default:
            throw "Never reach default";
    };
}

// Getters //

Piece Game::get_square(const square& p_sqr) {
    size_t x = p_sqr.x;
    size_t y = p_sqr.y;

    #ifndef NDEBUG
    if(x > 7 || y > 7) throw std::invalid_argument("indexed 0-7");
    #endif // NDEBUG
    
    uint32_t row = m_pieces[y];
    x = x << 2; // x *= 4;
    uint8_t result = 0 | (row >> x) & 0xf; // transfer piece to result
    return static_cast<Piece>(result);
}

// Private Member Functions //

void Game::decode_fen(const std::string& p_fen) noexcept {
    Fen::decode(this, p_fen); // Friend function mutates member vars

    #ifndef NDEBUG
    print_debug();
    #endif // NDEBUG
}

// Public Member Functions //

MoveInfo Game::check_move(const square& p_src, const square& p_dst) {
    Piece dst_piece = get_square(p_dst);
    if(dst_piece == Piece::None)
        return MoveInfo::FreeSquare;

    Piece src_piece = get_square(p_src);
    uint8_t src_color = (src_piece >> 3) & 1;
    uint8_t dst_color = (dst_piece >> 3) & 1;

    if(src_color == dst_color)
        return MoveInfo::OccupiedSquare;
    else if(dst_piece != Piece::WKing && dst_piece != Piece::BKing)
        return MoveInfo::Capture;
    else
        return MoveInfo::Check;
}

// Debug Functions //

#ifndef NDEBUG
void Game::print_debug() {
    for(int i = 7; i >= 0; --i) { // signed for decriments
        for(size_t j = 0; j < 8; j++) {
            Piece p = get_square(square(j, i));
            if(p == Piece::WPawn) std::cout << "P ";
            else if(p == Piece::BPawn) std::cout << "p ";
            else if(p == Piece::WBishop) std::cout << "B ";
            else if(p == Piece::BBishop) std::cout << "b ";
            else if(p == Piece::WKnight) std::cout << "N ";
            else if(p == Piece::BKnight) std::cout << "n ";
            else if(p == Piece::WRook) std::cout << "R ";
            else if(p == Piece::BRook) std::cout << "r ";
            else if(p == Piece::WQueen) std::cout << "Q ";
            else if(p == Piece::BQueen) std::cout << "q ";
            else if(p == Piece::WKing) std::cout << "K ";
            else if(p == Piece::BKing) std::cout << "k ";
            else std::cout << ". ";
        }
        std::cout << '\n';
    }
    std::cout << "\n\n";
}
#endif // NDEBUG

} // namespace sb
