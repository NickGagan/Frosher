/* Homepage header file */
#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include <sstream>
#include "GameState.h"
#include "Definitions.h"
#include "Instruction.h"
#include <iostream>

namespace Frosher{
class Homepage : public State{
public:
    Homepage(GameDataRef data);

    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);

private:
    GameDataRef _data;
    sf::Sprite _background;
    sf::Sprite _title;
    sf::Sprite _playButton;
    sf::Sprite _helpButton;
};
}
