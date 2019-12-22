/*	NameEnter cpp file
*		Including:
*			Switch to Highscore screen when user clicks on Continue button if the user did not obtain a high score
*/
#include "NameEnter.h"


namespace Frosher{
using namespace std;

NameEnter::NameEnter(GameDataRef data, int scoreValue) : _data(data), scoreValue(scoreValue) {}

void NameEnter::Init(){
    _data->assets.LoadTexture("NameEnter Background", NAMEENTER_BACKGROUND);
    _data->assets.LoadTexture("NameEnter Continue", NAMEENTER_CONTINUE);
    _data->assets.LoadFont("NameEnter font", FONT);

    _background.setTexture(this->_data->assets.GetTexture("NameEnter Background"));
    _continue.setTexture(this->_data->assets.GetTexture("NameEnter Continue"));

    text.setFont(this->_data->assets.GetFont("NameEnter font"));
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(40);
    text.setStyle(sf::Text::Regular);
    text.setPosition(300.f, 400.f);
    text.setLineSpacing(2);
    text.setString("A B C D E F G\nH I J K L M N\nO P Q R S T U\n  V W X Y Z");

    name.setFont(this->_data->assets.GetFont("NameEnter font"));
    name.setFillColor(sf::Color::White);
    name.setCharacterSize(80);
    name.setStyle(sf::Text::Regular);
    name.setPosition(400.f, 200.f);
    name.setLineSpacing(2);

    header.setFont(this->_data->assets.GetFont("NameEnter font"));
    header.setFillColor(sf::Color::White);
    header.setCharacterSize(40);
    header.setStyle(sf::Text::Regular);
    header.setPosition(200.f, 100.f);
    header.setLineSpacing(2);
    header.setString("Enter Name:");

    blocks.setFont(this->_data->assets.GetFont("NameEnter font"));
    blocks.setFillColor(sf::Color::White);
    blocks.setCharacterSize(90);
    blocks.setStyle(sf::Text::Regular);
    blocks.setPosition(390.f, 260.f);
    blocks.setLineSpacing(2);
    blocks.setString("---");

    _continue.setPosition((SCREEN_WIDTH / 1.6), (SCREEN_HEIGHT / 1.1) - (_continue.getGlobalBounds().height / 2));
}

void NameEnter::HandleInput(){
    sf::Event event;

    std::stringstream s;

    int gridXStart = 280;
    int gridXEnd = 820;
    int gridYStart = 390;
    int gridYEnd = 760;

    int xPos = 0;
    int yPos = 0;

    const int gridXCount = 7;
    const int gridYCount = 4;
    char letter[gridYCount][gridXCount] = { { 'A','B','C','D','E','F','G' },{ 'H','I','J','K','L','M','N' },{ 'O','P','Q','R','S','T','U' },{ ' ','V','W','X','Y','Z',' ' } };


    while (_data->window.pollEvent(event)){
        if (sf::Event::Closed == event.type){
            _data->window.close();
        }
        float Mx = sf::Mouse::getPosition(_data->window).x;
        float My = sf::Mouse::getPosition(_data->window).y;

        if (event.type == sf::Event::MouseButtonPressed && Mx > gridXStart && Mx < gridXEnd && My > gridYStart && My < gridYEnd){

            xPos = (Mx - gridXStart)*gridXCount / (gridXEnd - gridXStart);
            yPos = (My - gridYStart)*gridYCount / (gridYEnd - gridYStart);
            s << letter[yPos][xPos];
            if (letter_count < 3 && s.str().compare(" ") != 0){
                name_input.append(s.str());
                name.setString(name_input);
                letter_count = letter_count + 1;

            }
            s.str(std::string());
        }

        //When user clicks on Continue, goes to next screen
        if (_data->input.IsSpriteClicked(_continue, sf::Mouse::Left, _data->window)){
            //If the user obtained a high score, goes to NameEnter screen
            _data->machine.AddState(StateRef(new Highscore(_data, name_input, scoreValue)), true);
        }
    }
}

void NameEnter::Update(float dt) {}

void NameEnter::Draw(float dt){
    _data->window.clear();
    _data->window.draw(_background);
    _data->window.draw(_continue);
    _data->window.draw(text);
    _data->window.draw(name);
    _data->window.draw(header);
    _data->window.draw(blocks);

    _data->window.display();
}
}
