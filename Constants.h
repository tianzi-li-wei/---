#pragma once

namespace Xiangqi
{

    enum Side
    {
        SIDE_NONE  = 0,
        SIDE_RED   = 1,
        SIDE_BLACK = 2
    };

    enum PieceType
    {
        TYPE_NONE     = 0,
        TYPE_KING     = 1, // 将/帅
        TYPE_ADVISOR  = 2, // 士/仕
        TYPE_BISHOP   = 3, // 象/相
        TYPE_HORSE    = 4, // 马
        TYPE_ROOK     = 5, // 车
        TYPE_CANNON   = 6, // 炮
        TYPE_PAWN     = 7  // 兵/卒
    };

}