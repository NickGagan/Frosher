/* Header for handling the mouse position and if a sprite is clicked*/
#pragma once

#include <SFML/Graphics.hpp>

namespace Frosher{
class InputManager{
public:
    InputManager() {}
    ~InputManager() {}

    bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);

    sf::Vector2i GetMousePosition(sf::RenderWindow &window);
};
}
