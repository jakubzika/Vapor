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