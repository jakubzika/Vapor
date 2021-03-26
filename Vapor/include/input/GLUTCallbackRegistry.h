#pragma once

#include "GLUTInputsHandler.h"

#include "pgr.h"

namespace vpr {

class GLUTCallbackRegistry {
    public:


    static void mountEventListeners();

    static void setContext(GLUTInputsHandler* context) ;

    static void onKeyboardEvent(unsigned char key,int x, int y);
    static void onMouseMove(int x, int y);

    static void onMousePress(int button, int state, int x, int y);

    static GLUTInputsHandler* context;
    static bool initialized;
};


}