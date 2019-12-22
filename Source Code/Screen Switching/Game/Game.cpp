/*	Game cpp file
*			Generates AssetManager, StateMachine, InputManager
*/
#include "Game.h"
#include "Homepage.h"
#include "Obstacle.h"


namespace Frosher{
Game::Game(int width, int height, std::string title){
    _data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
    _data->machine.AddState(StateRef(new Homepage(this->_data)));
    this->Run();
}

void Game::Run(){
    while (this->_data->window.isOpen()){
        this->_data->machine.ProcessStateChanges();
        this->_data->machine.GetActiveState()->HandleInput();
        this->_data->machine.GetActiveState()->Update(dt);
        this->_data->machine.GetActiveState()->Draw(dt);
    }
}
}
