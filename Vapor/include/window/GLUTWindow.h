/**
 * \file       GLUTWindow.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Implementation of Window for GLUT library. Contains static functions due to glut not being able to access dynamic data. Only constant.
 *
*/

#pragma once


#include "pgr.h"

#include "Window.h"

namespace vpr {


class GLUTWindow : public Window{
    public:

    GLUTWindow(int width, int height): Window(width,height){}

    void init(int argc, char** argv);

    void setLoopContext(IWindowRenderer* windowRenderer);

    static void displayLoop();
    static IWindowRenderer* windowRendererContext;
    static GLUTWindow* instance;
    private:
};

}