/* GameState header file */

#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include "State.h"
#include "Game.h"
#include "movement.h"
#include "Obstacle.h"
#include "score.h"

// Header file for the Game Screen
namespace Frosher{
class GameState : public State{  // An extension of state
public:
    GameState(GameDataRef data); // constructor
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
private:
    GameDataRef _data;
    sf::Sprite _background;
    sf::Sprite _title;
    ObstManager obstacle_m; // The obstacle manager
    Player user; // The user's player
    clock_t t_prev; // Used for controlling animation speed (time of prev frame)
    clock_t t_prev_timer; // Used for controlling the
    Score gameScore; // The game score that is in the top right corner
    sf::View gameView; // Which part of the background is being viewed by the player
    int scaleFactor; // Used to help put in a background that is larger than the window
    void EndGame(); // Process to execute upon losing
    void WinGame(); // Process to execute upon winning

};
}
