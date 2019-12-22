#pragma once

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <stdlib.h>
#include <random>
#include "Definitions.h"
using namespace sf;
using namespace std;

// Class for a singular obstacle
class Obstacle{
public:
    Obstacle(string filename, int startPos);
    Sprite genObstacle(int height, RenderWindow& window);
    // Accessors for Obstacle Instance Variables
    Texture getTexture();
    Sprite& getSprite();
    Vector2u getSize();
    string getName();
    Vector2f getIncrement();
    int getStartPos();

private:
    string obstacleName; // Name of the obstacle file
    Texture obstacleTexture; // Obstacle texture
    Sprite obstacleSprite; //Obstacle Sprite
    Vector2u obstacleSize; // The size of the obstacle
    Vector2f obstacleIncrement; // The speed of the obstacle movement
    int startPos; // Start on left or right side of screen
    Vector2f setIncrement(string filename);// Mutator for the increment based on file name
};

class ObstManager{
public:
    ObstManager();
    /* Randomly pick the obstacles to appear on the screen
        Generate the sprite and move across the screen
        Draw the sprite in the window
     */
    void randomGen(RenderWindow& win);
    // Accessors
    vector<Obstacle> getObstacleOnScreen();
    vector<Obstacle> getObstacleOnScreen2();

private:
    vector<Obstacle> ObstacleArray;
    vector<Obstacle> ObstaclesOnScreen; // First set of obstacles on the screen
    vector<Obstacle> ObstaclesOnScreen2;// Second set of obstacles on the screen
    vector<int> randomNums; // The random indexes
};

int randInt();

