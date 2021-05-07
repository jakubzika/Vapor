#pragma once

#include "pgr.h"

#include "GLUTInputsHandler.h"
#include "GLUTCallbackRegistry.h"
#include "UserInput.h"

namespace vpr {


class GLUTUserInputHandler : public GLUTInputsHandler, public UserInputHandler  {


    public:
    GLUTUserInputHandler(int width, int height);

    void tick();
    void postTick();


    void setLockedCursor(bool state);

    void keyUpdate(KeyEnum key, bool state);
    void handleSpecialKeys();

    void onKeyPress(unsigned char key,int x, int y);
    void onKeyUp(unsigned char key,int x, int y);
    void onSpecialKeyPress(int key,int x, int y);
    void onSpecialKeyUp(int key,int x, int y);
    void onMouseMove(int x, int y);
    void onMousePress(int button, int state, int x, int y);

    private:
    bool firstTimeMouse{true};
    int width, height;
    
};


}