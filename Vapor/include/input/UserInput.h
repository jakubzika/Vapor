#pragma once

#include <map>

#include "../Types.h"

namespace vpr {

struct UserInput {
    int mouseX{0}, mouseY{0};
    int deltaMouseX{0}, deltaMouseY{0};

    bool leftMouseButton{false}, rightMouseButton{false};
    bool deltaLeftMouseButton{false}, deltaRightMouseButton{false};


    bool keyPressed[KeyEnum::SIZE];
    bool deltaKeyPressed[KeyEnum::SIZE];
    bool mouseLocked{false};
};

class UserInputHandler {
    public:
    UserInputHandler();
    virtual void tick() = 0;
    virtual void postTick() = 0;
    UserInput* getUserInput();
    virtual void setLockedCursor(bool state) = 0;


    private:

    protected:
    bool cursorLocked{false};
    UserInput userInput;
};

}