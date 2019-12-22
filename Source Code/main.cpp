
#include <iostream>
#include "Game.h"
#include "Definitions.h"

int main()
{
    srand(time(NULL));
    Frosher::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Frosher");
}
