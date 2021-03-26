#pragma once

#include <map>

#include "../Types.h"

namespace vpr {



struct UserInput {
    int mouseX, mouseY;
    int deltaMouseX, deltaMouseY;

    bool leftMouseButton, rightMouseButton;
    bool deltaLeftMouseButton, deltaRightMouseButton;


    bool keyPressed[KeyEnum::SIZE];
    bool deltaKeyPressed[KeyEnum::SIZE];

};

class UserInputHandler {
    public:
    UserInputHandler();
    virtual void tick();

    UserInput* getUserInput();

    private:

    protected:

    UserInput userInput;
};

}