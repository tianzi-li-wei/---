#include "ChessBoard.h"
#include "Constants.h"

ChessBoard::ChessBoard()
{
    initialize();
}

void ChessBoard::initialize()
{
    // 清空棋盘
    for(int y = 0; y < ROWS; ++y)
    {
        for(int x = 0; x < COLS; ++x)
        {
            board[y][x] = Piece();
        }
    }

    using namespace Xiangqi;

    //----------------------------------
    // 黑方
    //----------------------------------

    board[0][0] = Piece(SIDE_BLACK, TYPE_ROOK);
    board[0][1] = Piece(SIDE_BLACK, TYPE_HORSE);
    board[0][2] = Piece(SIDE_BLACK, TYPE_BISHOP);
    board[0][3] = Piece(SIDE_BLACK, TYPE_ADVISOR);
    board[0][4] = Piece(SIDE_BLACK, TYPE_KING);
    board[0][5] = Piece(SIDE_BLACK, TYPE_ADVISOR);
    board[0][6] = Piece(SIDE_BLACK, TYPE_BISHOP);
    board[0][7] = Piece(SIDE_BLACK, TYPE_HORSE);
    board[0][8] = Piece(SIDE_BLACK, TYPE_ROOK);

    board[2][1] = Piece(SIDE_BLACK, TYPE_CANNON);
    board[2][7] = Piece(SIDE_BLACK, TYPE_CANNON);

    board[3][0] = Piece(SIDE_BLACK, TYPE_PAWN);
    board[3][2] = Piece(SIDE_BLACK, TYPE_PAWN);
    board[3][4] = Piece(SIDE_BLACK, TYPE_PAWN);
    board[3][6] = Piece(SIDE_BLACK, TYPE_PAWN);
    board[3][8] = Piece(SIDE_BLACK, TYPE_PAWN);

    //----------------------------------
    // 红方
    //----------------------------------

    board[9][0] = Piece(SIDE_RED, TYPE_ROOK);
    board[9][1] = Piece(SIDE_RED, TYPE_HORSE);
    board[9][2] = Piece(SIDE_RED, TYPE_BISHOP);
    board[9][3] = Piece(SIDE_RED, TYPE_ADVISOR);
    board[9][4] = Piece(SIDE_RED, TYPE_KING);
    board[9][5] = Piece(SIDE_RED, TYPE_ADVISOR);
    board[9][6] = Piece(SIDE_RED, TYPE_BISHOP);
    board[9][7] = Piece(SIDE_RED, TYPE_HORSE);
    board[9][8] = Piece(SIDE_RED, TYPE_ROOK);

    board[7][1] = Piece(SIDE_RED, TYPE_CANNON);
    board[7][7] = Piece(SIDE_RED, TYPE_CANNON);

    board[6][0] = Piece(SIDE_RED, TYPE_PAWN);
    board[6][2] = Piece(SIDE_RED, TYPE_PAWN);
    board[6][4] = Piece(SIDE_RED, TYPE_PAWN);
    board[6][6] = Piece(SIDE_RED, TYPE_PAWN);
    board[6][8] = Piece(SIDE_RED, TYPE_PAWN);
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