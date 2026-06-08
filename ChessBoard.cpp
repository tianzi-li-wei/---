#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
    initialize();
}

void ChessBoard::initialize()
{
    for(int y = 0; y < ROWS; ++y)
    {
        for(int x = 0; x < COLS; ++x)
        {
            board[y][x] = Piece();
        }
    }
}

bool ChessBoard::inBoard(
    int x,
    int y) const
{
    return x >= 0 &&
           x < COLS &&
           y >= 0 &&
           y < ROWS;
}

Piece ChessBoard::getPiece(
    int x,
    int y) const
{
    if(!inBoard(x,y))
    {
        return Piece();
    }

    return board[y][x];
}

void ChessBoard::setPiece(
    int x,
    int y,
    const Piece& piece)
{
    if(!inBoard(x,y))
    {
        return;
    }

    board[y][x] = piece;
}