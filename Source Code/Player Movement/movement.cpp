/* Implementation of the character sprite and its animations*/
#include "movement.h"
using namespace std;
using namespace sf;


Player::Player(string playerTextureName){ // constructor
    x_start = 0; // the top left sprite sheet is the starting sprite
    y_start = 0;
    this->playerTexture.loadFromFile(playerTextureName);
    Sprite temp(this->playerTexture);
    this->playerSprite = temp;
    cropSprite(0);
    playerSprite.setOrigin(0,0);
    playerSprite.setPosition(480,960);
    animBit = -1; // no direction animation
    animStep = 0; // 0 step in animation
    animLock = 0; // Not locked into a certain animation
}

// Accessors
Sprite Player::getSprite(){return this->playerSprite;}
Texture Player::getTexture(){return this->playerTexture;}
int Player::getAnimStep(){return this->animStep;}
int Player::getAnimBit(){return this->animBit;}

// Mutator for the animation bit
void Player::setAnimBit(int dir){
    if(animLock == 0){ // only change the animation if not currently in a different one
        this->animBit = dir;
        animLock = 1; // once the animbit is set, we are locked into that animation until completion
    }
}
/*
    Alg for movement
    1. Move by 30 (1/4) of player size in direction x
    2. Crop sprite
    3. Step to the next frame
    4. Increment animStep
    5. If animStep = 4, then reset the three anim instance vars

*/
void Player::moveDown()
{
    if(playerSprite.getPosition().y < 960)
    {
        playerSprite.move(0, 30);
        cropSprite(2);
        frameStep(2);
        animStep += 1;
        if (animStep == 4)
        {
            animBit = -1;
            animStep = 0;
            animLock = 0;

        }
    }
    else
        animLock = 0;

}
void Player::moveUp()
{
    cropSprite(0);
    playerSprite.move(0, -30);
    frameStep(0);
    animStep += 1;
    if (animStep == 4)
    {
        animBit = -1;
        animStep = 0;
        animLock = 0;
    }
}
void Player::moveLeft(){
    if(playerSprite.getPosition().x > 0){
        playerSprite.move(-30, 0);
        cropSprite(3);
        frameStep(3);
        animStep += 1;
        if (animStep == 4)
        {
            animBit = -1;
            animStep = 0;
            \
            animLock = 0;
        }
    }
    else
        animLock = 0;
}

void Player::moveRight(){
    if(playerSprite.getPosition().x < 960){
        playerSprite.move(30, 0);
        cropSprite(1);
        frameStep(1);
        animStep += 1;
        if (animStep == 4){
            animBit = -1;
            animStep = 0;
            animLock = 0;
        }
    }
    else
        animLock = 0;
}

// Sprite Sheet functions
void Player::cropSprite(int dir){
    IntRect m_rect(x_start, y_start + y_size*dir, x_size, y_size);
    playerSprite.setTextureRect(m_rect); // Crop the sprite sheet based on the rectangle specified
}

void Player::frameStep(int dir){
    x_start+=x_size; // increment to the next frame (rightwards)
    x_start = x_start%playerTexture.getSize().x;
    cropSprite(dir);
}






