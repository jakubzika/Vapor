#pragma once


#include "pgr.h"


#include "GLUTInputsHandler.h"

namespace vpr {



class GLUTCallbackRegistry {

    public:
    static void mountEventListeners();

    static void setContext(GLUTInputsHandler* context);

    static void onKeyPress(unsigned char key,int x, int y);
    static void onKeyUp(unsigned char key,int x, int y);
    static void onSpecialKeyPress(int key,int x, int y);
    static void onSpecialKeyUp(int key,int x, int y);
    static void onMouseMove(int x, int y);

    static void onMousePress(int button, int state, int x, int y);

    static GLUTInputsHandler* context;
    static bool initialized;
};


}