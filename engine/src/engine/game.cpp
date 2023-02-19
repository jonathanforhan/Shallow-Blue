#include"game.hpp"
#include<sstream>
#include<vector>
#include<iostream>
#include<bitset>

namespace sb {

Game::Game(const std::string& p_fen) {
    decode_fen(p_fen);
}

// Setters //

void Game::set_pieces(uint32_t p_pieces[8]) {
    for(size_t i = 0; i < 64; ++i)
        this->m_pieces[i] = p_pieces[i];
}
void Game::set_turn(char p_turn) { this->m_turn = p_turn; }
void Game::set_castle(uint8_t p_castle) { this->m_castle = p_castle; }
void Game::set_en_passant(int8_t p_en_passant) { this->m_en_passant = p_en_passant; }
void Game::set_eval(uint8_t p_eval) { this->m_eval = p_eval; }

// Getters //

const uint32_t* Game::get_pieces(){ return m_pieces; }
const char Game::get_turn(){ return m_turn; }
const uint8_t Game::get_castle(){ return m_castle; }
const int8_t Game::get_en_passant(){ return m_en_passant; }
const uint8_t Game::get_eval(){ return m_eval; }

// Private Member Functions //

void Game::decode_fen(const std::string& p_fen) noexcept {
    // Parse Fen components then parse positonal string
    std::string buf;
    std::stringstream ss(p_fen);
    std::string position;

    ss >> buf; position = buf; // save position
    ss >> buf; m_turn = buf.c_str()[0];
    ss >> buf;
    for(const auto& n : buf) {
        switch(n) {
            case 'K':
                m_castle |= Castle::K;
                break;
            case 'k':
                m_castle |= Castle::k;
                break;
            case 'Q':
                m_castle |= Castle::Q;
                break;
            case 'q':
                m_castle |= Castle::q;
                break;
            default:
                m_castle = 0;
                break;
        }
    }
    ss >> buf; m_en_passant = buf[0] == '-' ? -1 : (buf[0] - 97) + ((buf[1] - 1) * 8);

    // Positional string parse
    ss = std::stringstream(position);
    size_t i = 0;
    while(std::getline(ss, buf, '/')) {
        int gap = 0;
        for(size_t j = 0; j < buf.length(); j++) {
            uint32_t color;
            if(std::isdigit(buf[j])) {
                gap += buf[j] - '1';
                continue;
            } else {
                color = std::isupper(buf[j]) ? 1 : 0; // w-1 b-0
                size_t offset = (j + gap) * 4;
                color = color << offset << 3;
                m_pieces[i] |= color;
            }

            uint32_t piece;
            switch(buf[j]) {
                case 'P':
                case 'p':
                    piece = Piece::Pawn;
                    break;
                case 'B':
                case 'b':
                    piece = Piece::Bishop;
                    break;
                case 'N':
                case 'n':
                    piece = Piece::Knight;
                    break;
                case 'R':
                case 'r':
                    piece = Piece::Rook;
                    break;
                case 'Q':
                case 'q':
                    piece = Piece::Queen;
                    break;
                case 'K':
                case 'k':
                    piece = Piece::King;
                    break;
                default:
                    piece = Piece::None;
            }

            size_t offset = (j + gap) * 4;
            piece = piece << offset;
            m_pieces[i] |= piece;
        }
        ++i;
    }
    for(auto& n : m_pieces) {
        std::cout << std::bitset<32>(n) << '\n';
    }
}

} // namespace sb
