#pragma once

#include "Constants.h"

struct Piece
{
    int side;
    int type;

    Piece(
        int s = Xiangqi::SIDE_NONE,
        int t = Xiangqi::TYPE_NONE)
        : side(s),
        type(t)
    {
    }

    bool isEmpty() const
    {
        return side == Xiangqi::SIDE_NONE;
    }
};