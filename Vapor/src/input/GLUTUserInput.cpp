#include <functional>
#include <memory>
#include <iostream>

#include "../../include/input/GLUTUserInput.h"
#include "../../include/input/GLUTCallbackRegistry.h"

namespace vpr {

GLUTUserInputHandler::GLUTUserInputHandler() {

    GLUTCallbackRegistry::setContext(this);
}


void GLUTUserInputHandler::tick() {

}

void GLUTUserInputHandler::onKeyboardEvent(unsigned char key,int x, int y) {
    std::cout << "key presss\n";
}

void GLUTUserInputHandler::onMouseMove(int x, int y) {

}

void GLUTUserInputHandler::onMousePress(int button, int state, int x, int y) {

}


}