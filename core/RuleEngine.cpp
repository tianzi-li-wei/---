#include "RuleEngine.h"
#include"Constants.h"
#include <cstdlib>
#include<algorithm>

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

    case Xiangqi::TYPE_KING:
        if(!validateKing(
                fromX,fromY,
                toX,toY))
            return false;
        break;

    case Xiangqi::TYPE_ADVISOR:
        if(!validateAdvisor(
                fromX,fromY,
                toX,toY))
            return false;
        break;

    case Xiangqi::TYPE_BISHOP:
        if(!validateElephant(
                fromX,fromY,
                toX,toY))
            return false;
        break;

    default:
        return false;
    }
    if(kingsFaceToFaceAfterMove(
            fromX,fromY,
            toX,toY))
    {
        return false;
    }

    return true;
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

bool RuleEngine::validateKing(
    int fromX,
    int fromY,
    int toX,
    int toY) const
{
    int dx = std::abs(toX - fromX);
    int dy = std::abs(toY - fromY);

    if(dx + dy != 1)
    {
        return false;
    }

    Piece king =
        board.getPiece(fromX,fromY);

    if(king.side == Xiangqi::SIDE_RED)
    {
        return toX >= 3 &&
               toX <= 5 &&
               toY >= 7 &&
               toY <= 9;
    }

    return toX >= 3 &&
           toX <= 5 &&
           toY >= 0 &&
           toY <= 2;
}

bool RuleEngine::validateAdvisor(
    int fromX,
    int fromY,
    int toX,
    int toY) const
{
    int dx = std::abs(toX - fromX);
    int dy = std::abs(toY - fromY);

    if(dx != 1 || dy != 1)
    {
        return false;
    }

    Piece advisor =
        board.getPiece(fromX,fromY);

    if(advisor.side == Xiangqi::SIDE_RED)
    {
        return toX >= 3 &&
               toX <= 5 &&
               toY >= 7 &&
               toY <= 9;
    }

    return toX >= 3 &&
           toX <= 5 &&
           toY >= 0 &&
           toY <= 2;
}

bool RuleEngine::validateElephant(
    int fromX,
    int fromY,
    int toX,
    int toY) const
{
    int dx = toX - fromX;
    int dy = toY - fromY;

    if(std::abs(dx) != 2 ||
        std::abs(dy) != 2)
    {
        return false;
    }

    int eyeX = fromX + dx / 2;
    int eyeY = fromY + dy / 2;

    if(!board.getPiece(
                  eyeX,
                  eyeY).isEmpty())
    {
        return false;
    }

    Piece elephant =
        board.getPiece(fromX,fromY);

    if(elephant.side == Xiangqi::SIDE_RED)
    {
        if(toY < 5)
            return false;
    }
    else
    {
        if(toY > 4)
            return false;
    }

    return true;
}

bool RuleEngine::kingsFaceToFaceAfterMove(
    int fromX,
    int fromY,
    int toX,
    int toY) const
{
    int redX=-1,redY=-1;
    int blackX=-1,blackY=-1;

    for(int y=0;y<10;y++)
    {
        for(int x=0;x<9;x++)
        {
            Piece p =
                board.getPiece(x,y);

            if(x==fromX && y==fromY)
            {
                p = Piece();
            }

            if(x==toX && y==toY)
            {
                p = board.getPiece(
                    fromX,
                    fromY);
            }

            if(p.type ==
                Xiangqi::TYPE_KING)
            {
                if(p.side ==
                    Xiangqi::SIDE_RED)
                {
                    redX=x;
                    redY=y;
                }
                else
                {
                    blackX=x;
                    blackY=y;
                }
            }
        }
    }

    if(redX != blackX)
    {
        return false;
    }

    int minY =
        std::min(redY,blackY);

    int maxY =
        std::max(redY,blackY);

    for(int y=minY+1;
         y<maxY;
         y++)
    {
        if(!board.getPiece(
                      redX,
                      y).isEmpty())
        {
            return false;
        }
    }

    return true;
}