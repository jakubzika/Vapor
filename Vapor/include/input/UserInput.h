#pragma once

#include <map>

namespace vpr {

struct UserInput {
    int mouseX, mouseY;
    int deltaMouseX, deltaMouseY;

    bool leftMouseButton, rightMouseButton;
    bool deltaLeftMouseButton, deltaRightMouseButton;


    std::map<unsigned char, bool> keyPressed;
    std::map<unsigned char, bool> deltaKeyPressed;

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