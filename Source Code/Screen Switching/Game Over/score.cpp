#include "score.h"
using namespace std;
using namespace sf;

Score::Score(){
    score = 1000;
    font.loadFromFile("Graphics/ARCADE_N.TTF");
    // Format the text
    scoreText.setFont(font);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setCharacterSize(40);
    scoreText.setStyle(sf::Text::Regular);
    scoreText.setLineSpacing(2);
    scoreText.setPosition(900.f, 10.f);
}

void Score::decrementScore(){
    this->score -= 10;
}

void Score::scrollScore(float y){
    scoreText.move(0.f, y);
}

// Accessors
Text Score::getScore()
{
    s << score;
    scoreText.setString(s.str());
    s.str(std::string());
    return scoreText;
}
int Score::getScoreVal(){return this-> score;}



