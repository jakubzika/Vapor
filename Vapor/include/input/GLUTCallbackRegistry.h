/**
 * \file       .h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Bypassing the issue with glut that its callbacks cannot contain class functions. Only pure functions, which static functions kind of are.
 *  Binds member methods of this class to glut. On event passes the events to non-static whatewer context. 
 *
*/

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