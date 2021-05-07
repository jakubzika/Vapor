#include <functional>
#include <memory>
#include <iostream>
#include <ctype.h>

#include "../../include/input/GLUTUserInput.h"
#include "../../include/input/GLUTCallbackRegistry.h"
#include "../../include/input/GLUTKeyMapping.h"

namespace vpr {

GLUTUserInputHandler::GLUTUserInputHandler(int width, int height) {
    this->width = width;
    this->height = height;
    GLUTCallbackRegistry::setContext(this);
    glutIgnoreKeyRepeat(1);
}


void GLUTUserInputHandler::tick() {
    for(int key = 0; key < KeyEnum::SIZE; key++) {
        this->userInput.deltaKeyPressed[key] = false;
    }

    this->userInput.deltaLeftMouseButton = false;
    this->userInput.deltaRightMouseButton = false;

    this->userInput.deltaMouseX = 0;
    this->userInput.deltaMouseY = 0;


}

void GLUTUserInputHandler::keyUpdate(KeyEnum key, bool state) {
    if(key == VPR_KEY_UNKNOWN) return;

    if(this->userInput.keyPressed[key] != state) {
        this->userInput.keyPressed[key] = state;
        this->userInput.deltaKeyPressed[key] = true;
    }

}

void GLUTUserInputHandler::handleSpecialKeys() {
    int specialKeysBitmap = glutGetModifiers();

    bool shiftValue = specialKeysBitmap & GLUT_ACTIVE_SHIFT;
    bool altValue = specialKeysBitmap & GLUT_ACTIVE_ALT;
    bool ctrlValue = specialKeysBitmap & GLUT_ACTIVE_CTRL;

    this->keyUpdate(VPR_KEY_SHIFT, shiftValue);
    this->keyUpdate(VPR_KEY_ALT, altValue);
    this->keyUpdate(VPR_KEY_CTRL, ctrlValue);

}

void GLUTUserInputHandler::onKeyPress(unsigned char keyCode,int x, int y) {    
    this->handleSpecialKeys();
    this->keyUpdate(charToKey(tolower(keyCode)), true);
}

void GLUTUserInputHandler::onKeyUp(unsigned char keyCode,int x, int y) {
    this->handleSpecialKeys();
    this->keyUpdate(charToKey(tolower(keyCode)), false);

}


void GLUTUserInputHandler::onSpecialKeyPress(int keyCode,int x, int y) {
    this->keyUpdate(specialToKey(keyCode), true);
    this->handleSpecialKeys();
}

void GLUTUserInputHandler::onSpecialKeyUp(int keyCode,int x, int y) {
    this->keyUpdate(specialToKey(keyCode), false);
    this->handleSpecialKeys();
}

void GLUTUserInputHandler::onMouseMove(int x, int y) {
    if(this->firstTimeMouse) {
        this->userInput.mouseX = x;
        this->userInput.mouseY = y;    

        this->userInput.deltaMouseX = 0;
        this->userInput.deltaMouseY = 0;
        this->firstTimeMouse = false;
        return;
    }

    int oldX = this->userInput.mouseX;
    int oldY = this->userInput.mouseY;

    this->userInput.mouseX = x;
    this->userInput.mouseY = y;

    this->userInput.deltaMouseX = x-oldX;
    this->userInput.deltaMouseY = y-oldY;

}

void GLUTUserInputHandler::onMousePress(int button, int state, int x, int y) {    
    bool pressed = state == 0;

    if((button == 0) && pressed != this->userInput.leftMouseButton) {
        this->userInput.leftMouseButton = pressed;
        this->userInput.deltaLeftMouseButton = true;
    }

    if((button == 2) && pressed != this->userInput.rightMouseButton) {
        this->userInput.rightMouseButton = pressed;
        this->userInput.deltaRightMouseButton = true;
    }
}   


void GLUTUserInputHandler::postTick() {

    if(this->cursorLocked) {
        glutWarpPointer(this->width/2,this->height/2);
        this->userInput.mouseX = this->width/2;
        this->userInput.mouseY = this->height/2;

    }
}


void GLUTUserInputHandler::setLockedCursor(bool state) {
    if(this->cursorLocked == state) return;
    this->userInput.mouseLocked = state;
    if(this->cursorLocked && state == false) {
        glutSetCursor(GLUT_CURSOR_INHERIT);
    } else {
        glutSetCursor(GLUT_CURSOR_NONE);
    }
    this->cursorLocked = state;

}


}