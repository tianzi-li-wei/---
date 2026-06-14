#pragma once

#include "Piece.h"

class ChessBoard
{
public:

    static constexpr int ROWS = 10;
    static constexpr int COLS = 9;

public:

    ChessBoard();

    void initialize();

    bool inBoard(
        int x,
        int y) const;

    Piece getPiece(
        int x,
        int y) const;

    void setPiece(
        int x,
        int y,
        const Piece& piece);

private:

    Piece board[ROWS][COLS];
};