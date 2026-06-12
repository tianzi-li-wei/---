#include "RuleEngine.h"
#include"Constants.h"
#include <cstdlib>

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
    if(!board.inBoard(fromX,fromY))
        return false;

    if(!board.inBoard(toX,toY))
        return false;

    Piece piece =
        board.getPiece(fromX,fromY);

    if(piece.isEmpty())
        return false;

    Piece target =
        board.getPiece(toX,toY);

    if(target.side == piece.side)
        return false;

    switch(piece.type)
    {
    case Xiangqi::TYPE_ROOK:
        return validateRook(
            fromX,fromY,
            toX,toY);

    case Xiangqi::TYPE_HORSE:
        return validateHorse(
            fromX,fromY,
            toX,toY);

    case Xiangqi::TYPE_CANNON:
        return validateCannon(
            fromX,fromY,
            toX,toY);

    case Xiangqi::TYPE_PAWN:
        return validatePawn(
            fromX,fromY,
            toX,toY);

    default:
        return false;
    }
}

MoveResult RuleEngine::movePiece(
    int fromX,
    int fromY,
    int toX,
    int toY)
{
    MoveResult result;

    if(!isValidMove(
            fromX,
            fromY,
            toX,
            toY))
    {
        return result;
    }

    Piece moving =
        board.getPiece(
            fromX,
            fromY);

    Piece target =
        board.getPiece(
            toX,
            toY);

    board.setPiece(
        toX,
        toY,
        moving);

    board.setPiece(
        fromX,
        fromY,
        Piece());

    result.success = true;

    if(target.type ==
        Xiangqi::TYPE_KING)
    {
        result.gameOver = true;
        result.winner = moving.side;
    }

    return result;
}

bool RuleEngine::isGameOver(
    int& winner) const
{
    winner = 0;

    return false;
}

bool RuleEngine::validateRook(
    int fromX,
    int fromY,
    int toX,
    int toY) const
{
    if(fromX != toX &&
        fromY != toY)
    {
        return false;
    }

    if(fromX == toX)
    {
        int step =
            (toY > fromY)
                ? 1
                : -1;

        for(int y = fromY + step;
             y != toY;
             y += step)
        {
            if(!board.getPiece(
                          fromX,
                          y).isEmpty())
            {
                return false;
            }
        }
    }
    else
    {
        int step =
            (toX > fromX)
                ? 1
                : -1;

        for(int x = fromX + step;
             x != toX;
             x += step)
        {
            if(!board.getPiece(
                          x,
                          fromY).isEmpty())
            {
                return false;
            }
        }
    }

    return true;
}

bool RuleEngine::validateHorse(
    int fromX,
    int fromY,
    int toX,
    int toY) const
{
    int dx = toX - fromX;
    int dy = toY - fromY;

    int adx = std::abs(dx);
    int ady = std::abs(dy);

    if(!((adx == 2 && ady == 1) ||
          (adx == 1 && ady == 2)))
    {
        return false;
    }

    if(adx == 2)
    {
        int legX =
            fromX + dx / 2;

        if(!board.getPiece(
                      legX,
                      fromY).isEmpty())
        {
            return false;
        }
    }
    else
    {
        int legY =
            fromY + dy / 2;

        if(!board.getPiece(
                      fromX,
                      legY).isEmpty())
        {
            return false;
        }
    }

    return true;
}

bool RuleEngine::validateCannon(
    int fromX,
    int fromY,
    int toX,
    int toY) const
{
    if(fromX != toX &&
        fromY != toY)
    {
        return false;
    }

    int count = 0;

    if(fromX == toX)
    {
        int step =
            (toY > fromY)
                ? 1
                : -1;

        for(int y = fromY + step;
             y != toY;
             y += step)
        {
            if(!board.getPiece(
                          fromX,
                          y).isEmpty())
            {
                count++;
            }
        }
    }
    else
    {
        int step =
            (toX > fromX)
                ? 1
                : -1;

        for(int x = fromX + step;
             x != toX;
             x += step)
        {
            if(!board.getPiece(
                          x,
                          fromY).isEmpty())
            {
                count++;
            }
        }
    }

    Piece target =
        board.getPiece(
            toX,
            toY);

    if(target.isEmpty())
    {
        return count == 0;
    }

    return count == 1;
}

bool RuleEngine::validatePawn(
    int fromX,
    int fromY,
    int toX,
    int toY) const
{
    Piece pawn =
        board.getPiece(
            fromX,
            fromY);

    int dx = toX - fromX;
    int dy = toY - fromY;

    if(std::abs(dx)
            +
            std::abs(dy)
        != 1)
    {
        return false;
    }

    if(pawn.side ==
        Xiangqi::SIDE_RED)
    {
        if(dy > 0)
            return false;

        bool crossedRiver =
            (fromY <= 4);

        if(!crossedRiver)
        {
            return dx == 0 &&
                   dy == -1;
        }

        return (dx == 0 &&
                dy == -1)
               ||
               (dy == 0 &&
                std::abs(dx) == 1);
    }

    if(pawn.side ==
        Xiangqi::SIDE_BLACK)
    {
        if(dy < 0)
            return false;

        bool crossedRiver =
            (fromY >= 5);

        if(!crossedRiver)
        {
            return dx == 0 &&
                   dy == 1;
        }

        return (dx == 0 &&
                dy == 1)
               ||
               (dy == 0 &&
                std::abs(dx) == 1);
    }

    return false;
}