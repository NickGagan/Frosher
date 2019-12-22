/*	Highscore screen
*		Including
*			Title at the top middle of the screen
*			Restart button at the bottom left of the screen
*			Exit button at the bottom right of the screen
*/
#include "Highscore.h"


namespace Frosher{
using namespace std;
Highscore::Highscore(GameDataRef data, string name, int scoreValue) : _data(data){
    readHighscore();
    while(name.length() < 3){ // If name entered is not 3 characters, append spaces to keep formatting
        name.append(" ");
    }
    updateHighscore(scoreValue, name);
    displayHighscore();
}

void Highscore::Init(){
    _data->assets.LoadTexture("Highscore State Background", HIGHSCORE_BACKGRROUND);
    _data->assets.LoadTexture("Highscore State Title", HIGHSCORE_TITLE);
    _data->assets.LoadTexture("Highscore State Restart", HIGHSCORE_RESTART);
    _data->assets.LoadTexture("Highscore State Exit", HIGHSCORE_EXIT);
    _data->assets.LoadFont("Highscore Font", FONT);

    _background.setTexture(this->_data->assets.GetTexture("Highscore State Background"));
    _title.setTexture(this->_data->assets.GetTexture("Highscore State Title"));
    _restart.setTexture(this->_data->assets.GetTexture("Highscore State Restart"));
    _exit.setTexture(this->_data->assets.GetTexture("Highscore State Exit"));
    text.setFont(this->_data->assets.GetFont("Highscore Font"));
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(40);
    text.setStyle(sf::Text::Regular);
    text.setPosition(250.f, 250.f);
    text.setLineSpacing(2);



    _title.setPosition((SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2), _title.getGlobalBounds().height / 2);
    _restart.setPosition((SCREEN_WIDTH / 7), (SCREEN_HEIGHT / 1.15) - (_restart.getGlobalBounds().height / 2));
    _exit.setPosition((SCREEN_WIDTH / 1.4), (SCREEN_HEIGHT / 1.15) - (_exit.getGlobalBounds().height / 2));
    saveHighscore();
}

void Highscore::HandleInput(){
    sf::Event event;
    while (_data->window.pollEvent(event)){
        if (sf::Event::Closed == event.type){
            _data->window.close();
        }

        //When players click the Restart button, go back to home screen
        if (_data->input.IsSpriteClicked(_restart, sf::Mouse::Left, _data->window)){
            _data->machine.AddState(StateRef(new Homepage(_data)), true);
        }

        //When players click the Exit buttonk, window closed
        if (_data->input.IsSpriteClicked(_exit, sf::Mouse::Left, _data->window)){
            _data->window.close();
        }
    }
}

void Highscore::Update(float dt) {}

void Highscore::Draw(float dt){
    _data->window.clear();

    _data->window.draw(_background);
    _data->window.draw(_restart);
    _data->window.draw(_exit);
    _data->window.draw(_title);
    _data->window.draw(text);

    _data->window.display();
}


void Highscore::readHighscore(){
    // open file
    ifstream file;
    file.open("highscores.txt");

    string text;


    for (int i = 0; getline(file, text); i++){
        if (i % 2 == 0)
            scoreArray[i / 2] = atoi(text.c_str());

        else
            nameArray[i / 2] = text;

    }
    file.close();
}

void Highscore::saveHighscore(){
    // open file
    ofstream file;
    file.open("highscores.txt");

    string text;


    for (int i = 0; i < SIZE; i++){
        file << scoreArray[i] << endl;
        file << nameArray[i] << endl;
    }
    file.close();
}

void Highscore::updateHighscore(int score, string name){
    bool flag = false;

    for (int i = 0; i < SIZE; i++){
        if (score > scoreArray[i] && !flag){
            prev_score = scoreArray[i];
            prev_user = nameArray[i];
            scoreArray[i] = score;
            nameArray[i] = name;
            flag = true;
        }
        else if (flag){
            temp_score = scoreArray[i];
            temp_user = nameArray[i];

            scoreArray[i] = prev_score;
            nameArray[i] = prev_user;

            prev_score = temp_score;
            prev_user = temp_user;
        }
    }
}

void Highscore::displayHighscore(){
    std::string data;
    std::stringstream s;
    for (int i = 0; i < SIZE; i++){
        data.append(nameArray[i]);
        data.append("\t\t");
        s << scoreArray[i];
        data.append(s.str());
        s.str(std::string());
        data.append("\n");
    }
    text.setString(data);
}

}
