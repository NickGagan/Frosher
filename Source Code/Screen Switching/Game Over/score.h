/* Header file for the score class
   This is used in the GameState screen*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>

using namespace std;
using namespace sf;

class Score{
public:
    Score(); // Constructor to initialize the text, fonts, and values of the game score

    // Accessors
    Text getScore();
    int getScoreVal();

    void decrementScore(); // Decrement the score by 10, called every second by game state
    void scrollScore(float y); // Used to scroll the score to keep it in the same fixed position in the top right

private:
    int score;
    Font font;
    stringstream s;
    Text scoreText;
};

