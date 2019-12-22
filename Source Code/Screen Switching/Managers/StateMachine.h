/*	StateMachine header file
*			Set up states and state switches
*/
#pragma once

#include <memory>
#include <stack>
#include "State.h"

namespace Frosher{
typedef std::unique_ptr<State> StateRef;

class StateMachine{
public:
    StateMachine() {}
    ~StateMachine() {}

    void AddState(StateRef newState, bool isReplacing = true); // Used for creating a new state
    void RemoveState(); // Remove a state

    void ProcessStateChanges();

    StateRef &GetActiveState();

private:
    std::stack<StateRef> _states;
    StateRef _newState;

    bool _isRemoving;
    bool _isAdding;
    bool _isReplacing;
};
}
