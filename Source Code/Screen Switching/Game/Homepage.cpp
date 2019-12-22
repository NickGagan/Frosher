/*	Homepage Screen
*	Including
*		Game logo at the top middle of the screen
*		Start button at the middle of the screen
*		Help button beneath the Start button, leads players to instruction screen
*/

#include "Homepage.h"

namespace Frosher{
Homepage::Homepage(GameDataRef data) : _data(data) {}

void Homepage::Init(){
    _data->assets.LoadTexture("Homepage State Background", HOMEPAGE_BACKGROUND);
    _data->assets.LoadTexture("Game Logo", HOMEPAGE_GAME_TITLE);
    _data->assets.LoadTexture("Play Button", HOMEPAGE_START_BUTTON);
    _data->assets.LoadTexture("Help Button", HOMEPAGE_HELP_BUTTON);

    _background.setTexture(this->_data->assets.GetTexture("Homepage State Background"));
    _title.setTexture(this->_data->assets.GetTexture("Game Logo"));
    _playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
    _helpButton.setTexture(this->_data->assets.GetTexture("Help Button"));

    _title.setPosition((SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2), _title.getGlobalBounds().height / 2);
    _playButton.setPosition((SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2));
    _helpButton.setPosition((SCREEN_WIDTH / 2.75), (SCREEN_HEIGHT / 1.5) - (_helpButton.getGlobalBounds().height / 2));
}

void Homepage::HandleInput(){
    sf::Event event;
    while (_data->window.pollEvent(event)){
        if (sf::Event::Closed == event.type){
            _data->window.close();
        }

        //When players click the Play button, game starts
        if (_data->input.IsSpriteClicked(_playButton, sf::Mouse::Left, _data->window)){
            _data->machine.AddState(StateRef(new GameState(_data)), true);
        }

        //When players click the Help button, move to instruction page
        if (_data->input.IsSpriteClicked(_helpButton, sf::Mouse::Left, _data->window)){
            _data->machine.AddState(StateRef(new Instruction(_data)), true);
        }
    }
}

void Homepage::Update(float dt) {}

void Homepage::Draw(float dt){
    _data->window.clear();

    _data->window.draw(_background);
    _data->window.draw(_title);
    _data->window.draw(_playButton);
    _data->window.draw(_helpButton);

    _data->window.display();
}
}
