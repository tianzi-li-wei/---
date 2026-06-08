#pragma once

#include "ChessBoard.h"
#include "MoveResult.h"

class RuleEngine
{
public:

    RuleEngine();

    void initializeBoard();

    bool isValidMove(
        int fromX,
        int fromY,
        int toX,
        int toY) const;

    MoveResult movePiece(
        int fromX,
        int fromY,
        int toX,
        int toY);

    bool isGameOver(
        int& winner) const;

    Piece queryPiece(
        int x,
        int y) const;

private:

    ChessBoard board;
};