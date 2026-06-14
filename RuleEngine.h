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
    int currentPlayer() const;

private:

    ChessBoard board;

private:
    int currentSide;

    bool validateRook(
        int fromX,
        int fromY,
        int toX,
        int toY) const;

    bool validateHorse(
        int fromX,
        int fromY,
        int toX,
        int toY) const;

    bool validateCannon(
        int fromX,
        int fromY,
        int toX,
        int toY) const;

    bool validatePawn(
        int fromX,
        int fromY,
        int toX,
        int toY) const;

    bool validateKing(
        int fromX,
        int fromY,
        int toX,
        int toY) const;

    bool validateAdvisor(
        int fromX,
        int fromY,
        int toX,
        int toY) const;

    bool validateElephant(
        int fromX,
        int fromY,
        int toX,
        int toY) const;

    bool kingsFaceToFaceAfterMove(
        int fromX,
        int fromY,
        int toX,
        int toY) const;
};