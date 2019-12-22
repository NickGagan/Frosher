//	Game Screen
#include <sstream>
#include "GameState.h"
#include "Definitions.h"
#include <iostream>
#include "Gameover.h"
#include "collision.h"
#include "NameEnter.h"



namespace Frosher{ // Constructor
GameState::GameState(GameDataRef data) : _data(data), obstacle_m(), user("animation.png"),
t_prev(std::clock()), t_prev_timer(std::clock()),gameScore(),
gameView(sf::FloatRect(0.f, 0.f, static_cast<float>(_data->window.getSize().x), static_cast<float>(_data->window.getSize().y))) {}


void GameState::Init(){
    _data->window.setFramerateLimit(30); // Controls the refresh rate of the game
    _data->assets.LoadTexture("Game State Background", GAME_BACKGROUND);

    _background.setTexture(this->_data->assets.GetTexture("Game State Background"));
    scaleFactor = 3;
    //distorts the background to fit the view, can make the background sprite larger than the view this way
    sf::Texture backTexture = this->_data->assets.GetTexture("Game State Background");
    _background.setScale((float)SCREEN_WIDTH / backTexture.getSize().x, scaleFactor*(float)SCREEN_HEIGHT / backTexture.getSize().y);

    _background.setPosition(0, -2*SCREEN_HEIGHT * (scaleFactor / 2));
    _data->window.setView(gameView); // set the game view
}

void GameState::HandleInput(){
    sf::Event event;
    while (_data->window.pollEvent(event)){
        if (sf::Event::Closed == event.type){
            _data->window.close();
        }
        if (event.type == sf::Event::KeyPressed){
            // based on the key press, select the designated player animation
            if (event.key.code == sf::Keyboard::Up){
                user.setAnimBit(0);
            }
            if (event.key.code == sf::Keyboard::Down){
                user.setAnimBit(2);
            }
            if (event.key.code == sf::Keyboard::Left){
                user.setAnimBit(3);
            }
            if (event.key.code == sf::Keyboard::Right){
                user.setAnimBit(1);
            }

        }
    }
}


void GameState::Update(float dt){
    if (this->user.getSprite().getPosition().y < SCREEN_HEIGHT/2 && gameView.getCenter().y >= (-SCREEN_HEIGHT - SCREEN_HEIGHT/2)){
        // If the player is past the middle of the bottom view then begin scrolling the screen upwards
        gameView.move(0.f, -3.0f);
        gameScore.scrollScore(-3.0f);
    }

    // Update the movement of the player
    clock_t t_curr = std::clock();
    if((t_curr - t_prev) > CLOCKS_PER_SEC/25){ //Every 1/25 second, execute the animation based on user.animBit
        if (user.getAnimBit() == 0){
            user.moveUp();
        }
        else if (user.getAnimBit() == 1){
            user.moveRight();
        }
        else if (user.getAnimBit() == 2){
            user.moveDown();
        }
        else if (user.getAnimBit() == 3){
            user.moveLeft();
        }
        t_prev = std::clock();
    }

    // Update the score at the top of the screen
    t_curr = std::clock();
    if((t_curr - t_prev_timer) > CLOCKS_PER_SEC){ // For every second decrement the score by 10
        t_prev_timer = std::clock();
        gameScore.decrementScore();
    }

    // If the player reaches the top of the screen, then execute the win game protocol
    if (user.getSprite().getPosition().y == -2*SCREEN_HEIGHT){
        WinGame();
    }

    // Function for if the player is approaching the top of the screen
    // Speed up the scrolling so that the spaces in front of the character are more visible
    if((user.getSprite().getPosition().y - (gameView.getCenter().y - SCREEN_HEIGHT/2)) <= 240){
        gameView.move(0.f, -8.0f);
        gameScore.scrollScore(-8.0f);
    }

    // If the player hits the bottom of the window while scrolling, they lose
    if ((user.getSprite().getPosition().y + 100) > (gameView.getCenter().y+SCREEN_HEIGHT/2)){
        EndGame();
    }

    // Code for checking the collisions
    std::vector<Obstacle> temp = obstacle_m.getObstacleOnScreen();
    std::vector<Obstacle> temp2 = obstacle_m.getObstacleOnScreen2();
    for (int i = 0; i < NUMOBSTACLES; ++i){
        if (Collision::PixelPerfectTest(user.getSprite(), temp[i].getSprite())||Collision::PixelPerfectTest(user.getSprite(), temp2[i].getSprite()))    //array of sprites{
            EndGame();
        }
    }


void GameState::Draw(float dt){
    _data->window.clear();
    _data->window.draw(_background); // draw background
    _data->window.setView(gameView); // set the game view
    _data->window.draw(user.getSprite()); // draw the player sprite
    obstacle_m.randomGen(_data->window); // draw the obstacles
    _data->window.draw(gameScore.getScore()); // draw the gameScore
    _data->window.display();
}
void GameState::EndGame(){ // Lost game
    Draw(1.0f/60.0f); // Draw the next frame
    sf::sleep(seconds(1));
    gameView.setCenter(SCREEN_WIDTH/2, SCREEN_HEIGHT/2); // Fix the view for the next state
    _data->machine.AddState(StateRef(new Gameover(_data)), true); // Proceed to the game over screen

}
void GameState::WinGame(){ // Won game
    Draw(1.0f/60.0f); // Draw the next frame
    sf::sleep(seconds(1));
    gameView.setCenter(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    _data->machine.AddState(StateRef(new NameEnter(_data, gameScore.getScoreVal())), true); // Proceed to the entering name screen

}
}
