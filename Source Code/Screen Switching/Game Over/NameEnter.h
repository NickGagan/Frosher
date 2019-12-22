/*	NameEnter header file
This is the screen for entering the player name to later add to the highscore screen
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <string>
#include "State.h"
#include "Game.h"
#include "Highscore.h"
#include "Definitions.h"

namespace Frosher{
class NameEnter : public State{
public:
    NameEnter(GameDataRef data, int scoreValue);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);

private:
    GameDataRef _data;
    sf::Sprite _background;
    sf::Sprite _continue;
    sf::Text text;
    sf::Text name;
    sf::Text header;
    sf::Text blocks;
    int letter_count = 0;
    int scoreValue;
    std::string name_input;
};
}
