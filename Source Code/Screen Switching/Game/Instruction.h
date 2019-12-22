/*	Instruction header file */

#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace Frosher
{
class Instruction : public State
{
public:
    Instruction(GameDataRef data);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);

private:
    GameDataRef _data;
    sf::Sprite _background;
    sf::Sprite _returnButton;
    sf::Sprite _title;
};
}
