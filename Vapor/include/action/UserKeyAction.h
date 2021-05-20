/**
 * \file       UserKeyAction.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      Handling user input and setting app state
 *
 *  Handles generic key presses which modify game state(fog, wireframe mode)
 *  Sets values on static AppState
 *
*/

#pragma once

#include "pgr.h"

#include "IAction.h"
#include "../input/UserInput.h"
#include "../engine/State.h"

namespace vpr {

class UserKeyAction : public IAction {

    public:
    UserKeyAction(UserInput* input);
    void tick(long msec);
    bool isFinished() {return false;}

    private:
    UserInput* input;
};

}