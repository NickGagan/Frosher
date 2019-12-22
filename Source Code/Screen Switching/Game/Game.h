/*	Game header file
* 		Generates AssetManager, InputManager, StateMachine
*/
#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "StateMachine.h"
#include "InputManager.h"

namespace Frosher{
struct GameData{
    StateMachine machine;
    sf::RenderWindow window;
    AssetManager assets;
    InputManager input;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game{
public:
    Game(int width, int height, std::string title);

private:

    GameDataRef _data = std::make_shared<GameData>();
    float dt = 1.0f/60.0f;
    void Run();
};
}
