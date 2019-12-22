/*	Instruction Screen
*	Including
*		Title at the top middle of the screen
*		Rules at the middle of the screen
*		Back button at the buttom right of the screen
*/

#include <sstream>
#include "Instruction.h"
#include "Homepage.h"
#include "Definitions.h"
#include <iostream>

namespace Frosher
{
Instruction::Instruction(GameDataRef data) : _data(data) {}

void Instruction::Init()
{
    _data->assets.LoadTexture("Instruction State Background", INSTRUCTION_BACKGROUND);
    _data->assets.LoadTexture("Return Button", INSTRUCTION_RETURN_BUTTON);
    _data->assets.LoadTexture("Instruction State Title", INSTRUCTION_TITLE);

    _background.setTexture(this->_data->assets.GetTexture("Instruction State Background"));
    _returnButton.setTexture(this->_data->assets.GetTexture("Return Button"));
    _title.setTexture(this->_data->assets.GetTexture("Instruction State Title"));

    _title.setPosition((SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2), _title.getGlobalBounds().height / 2);
    _returnButton.setPosition((SCREEN_WIDTH / 1.3), (SCREEN_HEIGHT / 1.1) - (_returnButton.getGlobalBounds().height / 2));

}

void Instruction::HandleInput()
{
    sf::Event event;
    while (_data->window.pollEvent(event))
    {
        if (sf::Event::Closed == event.type)
        {
            _data->window.close();
        }

        //When players click the Back button, go back to home screen
        if (_data->input.IsSpriteClicked(_returnButton, sf::Mouse::Left, _data->window))
        {
            _data->machine.AddState(StateRef(new Homepage(_data)), true);
        }

    }
}

void Instruction::Update(float dt) {}

void Instruction::Draw(float dt)
{
    _data->window.clear();

    _data->window.draw(_background);
    _data->window.draw(_returnButton);
    _data->window.draw(_title);

    _data->window.display();
}
}
