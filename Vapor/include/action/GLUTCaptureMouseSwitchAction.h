/**
 * \file       GLUTCaptureMouseSwitchAction.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  depreceated- not in use
 *
*/

#pragma once

#include "../input/UserInput.h"
#include "IAction.h"

namespace vpr {

class GLUTCaptureMouseSwitchAction : public IAction {

    public:
    GLUTCaptureMouseSwitchAction(UserInput* input, int width, int height, UserInputHandler* handler);
    void tick(long msec);
    bool isFinished() {return false;}

    private:

    bool enabled{false};
    UserInput* input;
    UserInputHandler* handler;
    int width, height;

};

}