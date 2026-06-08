#include "RuleEngine.h"

RuleEngine::RuleEngine()
{
    initializeBoard();
}

void RuleEngine::initializeBoard()
{
    board.initialize();
}

Piece RuleEngine::queryPiece(
    int x,
    int y) const
{
    return board.getPiece(x,y);
}

bool RuleEngine::isValidMove(
    int fromX,
    int fromY,
    int toX,
    int toY) const
{
    (void)fromX;
    (void)fromY;
    (void)toX;
    (void)toY;

    return false;
}

MoveResult RuleEngine::movePiece(
    int fromX,
    int fromY,
    int toX,
    int toY)
{
    (void)fromX;
    (void)fromY;
    (void)toX;
    (void)toY;

    MoveResult result;

    return result;
}

bool RuleEngine::isGameOver(
    int& winner) const
{
    winner = 0;

    return false;
}