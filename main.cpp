#include <iostream>

#include "RuleEngine.h"

int main()
{
    RuleEngine engine;

    Piece p = engine.queryPiece(4,4);

    std::cout
        << "side = "
        << p.side
        << " type = "
        << p.type
        << std::endl;

    return 0;
}
