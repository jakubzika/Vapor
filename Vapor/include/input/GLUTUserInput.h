#pragma once

#include "pgr.h"

#include "GLUTInputsHandler.h"
#include "UserInput.h"

namespace vpr {



class GLUTUserInputHandler : public GLUTInputsHandler, public UserInputHandler  {


    public:
    GLUTUserInputHandler();

    void tick();
    
    void onKeyboardEvent(unsigned char key,int x, int y);
    void onMouseMove(int x, int y);
    void onMousePress(int button, int state, int x, int y);
};


}