#include <iostream>

#include "../../include/action/GLUTCaptureMouseSwitchAction.h"

namespace vpr {

GLUTCaptureMouseSwitchAction::GLUTCaptureMouseSwitchAction(UserInput* input, int width, int height, UserInputHandler* handler) {
    this->input = input;
    this->width = width;
    this->handler = handler;
    this->height = height;
}

void GLUTCaptureMouseSwitchAction::tick(long msec) {

}

}