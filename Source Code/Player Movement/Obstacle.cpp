/* Implementation files for the Obstacle Classes*/
#include "Obstacle.h"
using namespace sf;
using namespace std;

// Obstacle Constructor
Obstacle::Obstacle(string filename, int startPos){
    this -> obstacleName = filename;
    this -> obstacleTexture.loadFromFile(filename);
    Sprite temp(this-> obstacleTexture);
    this -> obstacleSprite = temp;
    obstacleSprite.setScale(5, 5); // increase the size of the png
    this->obstacleSize = this->obstacleTexture.getSize();
    this->obstacleSize.x *= 5;
    this ->obstacleSize.y *= 5;
    if (startPos == 0) // determine the position based on integer param
        obstacleSprite.setPosition(-1*int(obstacleSize.x), 0);
    else
        obstacleSprite.setPosition(SCREEN_WIDTH, 0);

    // Increment is the speed of the obstacle movement
    this -> obstacleIncrement = setIncrement(filename);
    this-> startPos = startPos;
}

// Implementation of Accessors

Vector2u Obstacle::getSize(){return obstacleSize;}
Texture Obstacle::getTexture(){return this->obstacleTexture;}
int Obstacle::getStartPos(){return this->startPos;}
string Obstacle::getName(){return obstacleName;}
Vector2f Obstacle::getIncrement(){return this->obstacleIncrement;}

Sprite& Obstacle::getSprite(){
    obstacleTexture.loadFromFile(this->obstacleName);
    obstacleSprite.setTexture(obstacleTexture);
    return obstacleSprite;
}


// Set the velocities of each obstacle based on the file name
Vector2f Obstacle::setIncrement(string filename){
    Vector2f increment(0.0f, 0.0f);
    if (filename == GREEN_CAR || filename == GREEN_CAR1 || filename == RED_CAR || filename == RED_CAR1 || filename == BLUE_CAR || filename == BLUE_CAR1)
        increment.x = 8.0f;
    else if (filename == BIKER || filename == BIKER1 )
        increment.x = 5.0f;
    else if (filename == DEAN || filename == ALUMNI)
        increment.x = 3.8f;
    else if (filename == SKATEBOARD)
        increment.x = 4.2f;
    else if (filename == KBUS || filename == KBUS1 || filename ==KBUS_D || filename == KBUS_D1 )
        increment.x = 7.0f;
    return increment;
}

// Generate the obstacle and move across the screen
Sprite Obstacle::genObstacle(int height, RenderWindow& window){
    // change the y coordinate of the height
    obstacleSprite.setPosition(obstacleSprite.getPosition().x, height*int(obstacleSize.y));
    if(this->startPos == 0){ // For start position on the left
        if(obstacleSprite.getPosition().x - obstacleSize.x < window.getSize().x){// move across screen
            obstacleSprite.setPosition(obstacleSprite.getPosition() + obstacleIncrement);
        }
        else{ // reset to orginal position if off the screen
            obstacleSprite.setPosition(-1*int(obstacleSize.x), height*int(obstacleSize.y));
        }
    }else{ // For start position on the right
        if(obstacleSprite.getPosition().x + obstacleSize.x > 0){
            obstacleSprite.setPosition(obstacleSprite.getPosition() - obstacleIncrement);
        }
        else{ // If off the screen then reset the position
            obstacleSprite.setPosition(SCREEN_WIDTH, height*int(obstacleSize.y));
        }
    }
    return this->obstacleSprite;
}

/* Implementation of obstacle manager */

ObstManager::ObstManager(){
    // Create a vector of every possible Obstacle
    ObstacleArray.push_back(Obstacle(ALUMNI, 0));
    ObstacleArray.push_back(Obstacle(ALUMNI, 1));
    ObstacleArray.push_back(Obstacle(BIKER, 0));
    ObstacleArray.push_back(Obstacle(BIKER1, 1));
    ObstacleArray.push_back(Obstacle(BLUE_CAR, 0));
    ObstacleArray.push_back(Obstacle(BLUE_CAR1, 1));
    ObstacleArray.push_back(Obstacle(DEAN, 0));
    ObstacleArray.push_back(Obstacle(DEAN, 1));
    ObstacleArray.push_back(Obstacle(GREEN_CAR, 0));
    ObstacleArray.push_back(Obstacle(GREEN_CAR1, 1));
    ObstacleArray.push_back(Obstacle(KBUS, 0));
    ObstacleArray.push_back(Obstacle(KBUS1, 1));
    ObstacleArray.push_back(Obstacle(KBUS_D, 0));
    ObstacleArray.push_back(Obstacle(KBUS_D1,1));
    ObstacleArray.push_back(Obstacle(RED_CAR, 0));
    ObstacleArray.push_back(Obstacle(RED_CAR1, 1));
    ObstacleArray.push_back(Obstacle(SKATEBOARD, 0));
    ObstacleArray.push_back(Obstacle(SKATEBOARD, 1));
    for (int i = 0; i < NUMOBSTACLES; i++){
        randomNums.push_back(randInt()); // Random indexes to refer to an obstacle
    }
    for (int i = 0; i < int(randomNums.size()); i++){
        // Add the random obstacles to the two arrays of obstacles on the page
        Obstacle obstacle_to_add = ObstacleArray[randomNums[i]];
        ObstaclesOnScreen.push_back(Obstacle(ObstacleArray[randomNums[i]].getName(), ObstacleArray[randomNums[i]].getStartPos()));
        ObstaclesOnScreen2.push_back(Obstacle(ObstacleArray[randomNums[i]].getName(), ObstacleArray[randomNums[i]].getStartPos()));
       // Set the start positions of the second obstacles
        if(ObstaclesOnScreen2[i].getStartPos() == 1)
            ObstaclesOnScreen2[i].getSprite().setPosition(SCREEN_WIDTH*1.5, ObstaclesOnScreen2[i].getSprite().getPosition().y);
        else
            ObstaclesOnScreen2[i].getSprite().setPosition(-SCREEN_WIDTH*0.8, ObstaclesOnScreen2[i].getSprite().getPosition().y);
    }
}

// Generate all the obstacles on the screen
void ObstManager::randomGen(RenderWindow& win){
    // negative number because the heights above the starting view are negative
    for(int i = -17; i < int(ObstaclesOnScreen.size()) - 17; i++){
        // Generate each obstacle in the array
        ObstaclesOnScreen[i+17].genObstacle(i,win);
        ObstaclesOnScreen2[i+17].genObstacle(i,win);
        // Ignore the heights where roads are not present
        if (i == 0||i == 1||i == 4||i == -3||i == -7||i == -9||i == -13||i == -15){
            ObstaclesOnScreen[i+17].getSprite().setPosition(0, 1080);
            ObstaclesOnScreen2[i+17].getSprite().setPosition(0, 1080);
        }
        // Draw the obstacles on the window
        win.draw(ObstaclesOnScreen[i+17].getSprite());
        win.draw(ObstaclesOnScreen2[i+17].getSprite());
    }
}

// Accessors for the obstacles on the screen
vector<Obstacle> ObstManager::getObstacleOnScreen(){
    vector<Obstacle> temp;
    for (int i = 0; i < NUMOBSTACLES; i++){
        temp.push_back(ObstaclesOnScreen[i]);
    }
    return temp;
}

vector<Obstacle> ObstManager::getObstacleOnScreen2(){
    vector<Obstacle> temp;
    for (int i = 0; i < NUMOBSTACLES; i++){
        temp.push_back(ObstaclesOnScreen2[i]);
    }
    return temp;
}

// Random integer for the obstacle array
int randInt(){
    return rand()%18;
}

