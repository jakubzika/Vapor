
#include "../../include/input/UserInput.h"

namespace vpr {

UserInputHandler::UserInputHandler() {
    for(int i = KeyEnum::Begin+1; i < KeyEnum::SIZE; ++i) {
        this->userInput.keyPressed[i] = false;
        this->userInput.deltaKeyPressed[i] = false;
    }

    
}

UserInput* UserInputHandler::getUserInput() {
    return &(this->userInput);
}


}