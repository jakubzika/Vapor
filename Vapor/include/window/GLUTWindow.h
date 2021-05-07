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