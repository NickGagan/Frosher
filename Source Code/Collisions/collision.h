// Header file for collisions
#include <SFML/Graphics.hpp>
#include <string>
#ifndef COLLISION_H
#define COLLISION_H

namespace Collision
{

// Test for a collision between two sprites by comparing the alpha values of overlapping pixels
// AlphaLimit: The threshold at which a pixel becomes "solid". If AlphaLimit is 127, a pixel with
// alpha value 128 will cause a collision and a pixel with alpha value 126 will not.
bool PixelPerfectTest(const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit = 0);
}

#endif
