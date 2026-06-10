#include <iostream>
#include "RuleEngine.h"

int main()
{
    RuleEngine engine;

    Piece p1 = engine.queryPiece(0,0);
    Piece p2 = engine.queryPiece(4,0);
    Piece p3 = engine.queryPiece(4,9);
    Piece p4 = engine.queryPiece(1,7);

    std::cout
        << p1.side << " "
        << p1.type << std::endl;

    std::cout
        << p2.side << " "
        << p2.type << std::endl;

    std::cout
        << p3.side << " "
        << p3.type << std::endl;

    std::cout
        << p4.side << " "
        << p4.type << std::endl;

    return 0;
}