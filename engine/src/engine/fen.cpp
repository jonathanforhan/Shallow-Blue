#include"fen.hpp"
#include<sstream>

namespace sb {
 
/* Each piece takes 4 bits, [1  color bit ][ 3 id bits based on Piece enum ]
 * encoded bottom to top left to right such that piece [0][0] is the white rook
 */

void Fen::decode(Game* p_game, const std::string& p_fen) {
    // Parse Fen components then parse positonal string
    std::string buf;
    std::stringstream ss(p_fen);
    std::string position;

    ss >> buf; position = buf; // save position
    ss >> buf; p_game->m_turn = buf.c_str()[0];
    ss >> buf;
    for(const auto& n : buf) {
        switch(n) {
            case 'K':
                p_game->m_castle |= Castle::K; break;
            case 'k':
                p_game->m_castle |= Castle::k; break;
            case 'Q':
                p_game->m_castle |= Castle::Q; break;
            case 'q':
                p_game->m_castle |= Castle::q; break;
            default:
                p_game->m_castle = 0;
        }
    }
    ss >> buf; p_game->m_en_passant = buf[0] == '-' ? -1 : (buf[0] - 97) + ((buf[1] - 1) * 8);

    // Positional string parse
    ss = std::stringstream(position);
    size_t i = 7;
    while(std::getline(ss, buf, '/')) {
        int gap = 0;
        for(size_t j = 0; j < buf.length(); j++) {
            size_t offset = (j + gap) * 4;
            if(std::isdigit(buf[j])) {
                gap += buf[j] - '1'; // -'1' and not -'0' to offset j incriment
                continue;
            } else if(std::isupper(buf[j])){
                uint32_t color = 1 << offset << 3; // white piece
                p_game->m_pieces[i] |= color;
            }

            uint32_t piece;
            switch(buf[j]) {
                case 'P':
                case 'p':
                    piece = PieceNoColor::Pawn; break;
                case 'B':
                case 'b':
                    piece = PieceNoColor::Bishop; break;
                case 'N':
                case 'n':
                    piece = PieceNoColor::Knight; break;
                case 'R':
                case 'r':
                    piece = PieceNoColor::Rook; break;
                case 'Q':
                case 'q':
                    piece = PieceNoColor::Queen; break;
                case 'K':
                case 'k':
                    piece = PieceNoColor::King; break;
                default:
                    piece = Piece::None;
            }
            piece = piece << offset;
            p_game->m_pieces[i] |= piece;
        }
        --i;
    }
}

} // namespace sb
