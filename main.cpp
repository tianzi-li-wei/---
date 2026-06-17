#include <iostream>
#include "RuleEngine.h"

int main()
{
    RuleEngine engine;

    std::cout
        << engine.currentPlayer()
        << std::endl;

    engine.movePiece(
        2,6,
        2,5);

    std::cout
        << engine.currentPlayer()
        << std::endl;

    engine.movePiece(
        2,3,
        2,4);

    std::cout
        << engine.currentPlayer()
        << std::endl;

    return 0;
}