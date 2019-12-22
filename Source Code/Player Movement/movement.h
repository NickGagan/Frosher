#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;

class Player
{
public:
    Player(string playerTextureName);
    // Accessors
    Sprite getSprite();
    Texture getTexture();
    int getAnimBit();
    int getAnimStep();
    // Movement Functions
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    // Crop the sprite sheet to get the wanted picture
    void cropSprite(int dir);
    // Step to the next frame in the animation
    void frameStep(int dir);
    void setAnimBit(int dir); // Mutator for GameState to set which animation player should execute

private:
    Sprite playerSprite;
    Texture playerTexture;
    int x_start, y_start; // where on the sprite sheet we are cropping from
    // The dimensions of the player
    const int x_size = 120;
    const int y_size = 120;
    int animBit; // 0: up, 1: right, 2:down, 3: left to dictate what animation we are executing
    int animStep; // indicates which frame of the animation we are currently in
    bool animLock; // If animLock is true, the player sprite is stuck in its current animation sequence

};





