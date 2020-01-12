#pragma once

namespace Chess
{
enum class Piece
{
    KING,
    KING_CASTLE,
    QUEEN,
    PAWN,
    PAWN_EN_PASSANT,
    ROOK,
    ROOK_CASTLE,
    KNIGHT,
    BISHOP,
    NONE,
    OUT_OF_BOUNDS
};
}