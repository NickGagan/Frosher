/*	State header file
*			Used for the different steps executed in each state
            1. Init
            2. Handle Input
            3. Update
            4. Draw
*/
#pragma once

namespace Frosher{
class State{
public:
    virtual void Init() = 0; // Init the state

    virtual void HandleInput() = 0; // Handle any user input
    virtual void Update(float dt) = 0; //Update the positions of sprites, instance variables etc
    virtual void Draw(float dt) = 0; // Draw to the screen

    virtual void Pause() {}
    virtual void Resume() {}
};
}
