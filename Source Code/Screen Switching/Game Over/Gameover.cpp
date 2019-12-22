/*	Gameover cpp file
*		Including:
*			Backgroud image with "Game over"
* 			Continue button beneath "Game over"
*			Switch to Highscore screen when user clicks on Continue button if the user did not obtain a high score
*			Switch to NameEnter screen when user clicks on Continue button if the user obtained a high score
*/
#include <sstream>
#include <iostream>
#include "Gameover.h"
#include "NameEnter.h"
#include "Highscore.h"
#include "Definitions.h"

namespace Frosher
{
Gameover::Gameover(GameDataRef data) : _data(data) {}

void Gameover::Init()
{
    _data->assets.LoadTexture("Gameover Background", GAMEOVER_BACKGROUND);
    _data->assets.LoadTexture("Gameover Continue", GAMEOVER_CONTINUE);

    _background.setTexture(this->_data->assets.GetTexture("Gameover Background"));
    _continue.setTexture(this->_data->assets.GetTexture("Gameover Continue"));

    _continue.setPosition((SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 1.5) - (_continue.getGlobalBounds().height / 2));
}

void Gameover::HandleInput()
{
    sf::Event event;
    while (_data->window.pollEvent(event))
    {
        if (sf::Event::Closed == event.type)
        {
            _data->window.close();
        }

        //When user clicks on Continue, goes to next screen
        if (_data->input.IsSpriteClicked(_continue, sf::Mouse::Left, _data->window))
        {
            //If the user obtained a high score, goes to NameEnter screen

            _data->machine.AddState(StateRef(new Highscore(_data, "", 0)), true);
        }
    }
}

void Gameover::Update(float dt) {}

void Gameover::Draw(float dt)
{
    _data->window.clear();

    _data->window.draw(_background);
    _data->window.draw(_continue);

    _data->window.display();
}
}
