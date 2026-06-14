#include <iostream>
#include "RuleEngine.h"

int main()
{
    RuleEngine engine;

    std::cout
        << engine.isValidMove(
               6,5,
               8,3)
        << std::endl;

    return 0;
}