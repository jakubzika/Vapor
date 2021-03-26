#include "../../include/input/UserInput.h"

namespace vpr {

UserInputHandler::UserInputHandler() {
    
}

UserInput* UserInputHandler::getUserInput() {
    return &(this->userInput);
}

void UserInputHandler::tick() {

}

}