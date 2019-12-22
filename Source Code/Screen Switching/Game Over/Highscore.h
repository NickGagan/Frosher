/*	Highscore screen header file  */
#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Homepage.h"
#include "Definitions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "GameState.h"


#define SIZE 5

namespace Frosher
{
using namespace std;

class Highscore : public State{
public:
    Highscore(GameDataRef data, string name, int scoreValue);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);

    // Accessors
    void readHighscore(); // read the highscores from the file
    void saveHighscore(); // Save the new highscores to the file
    void updateHighscore(int score, string name); // update the highscores
    void displayHighscore(); // display the highscores on the screen


private:
    GameDataRef _data;
    sf::Sprite _background;
    sf::Sprite _restart;
    sf::Sprite _exit;
    sf::Sprite _title;
    sf::Text text;

    string nameArray[SIZE];
    int scoreArray[SIZE];
    string name; // Name of player
    // Instance variables to help reformat the table if an insertion occurs
    int temp_score;
    int prev_score;
    string temp_user;
    string prev_user;
};
}
