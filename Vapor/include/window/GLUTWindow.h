#pragma once


#include "pgr.h"

#include "Window.h"

namespace vpr {

class GLUTWindow : public Window{
    public:

    GLUTWindow(int width, int height): Window(width,height){}

    void init(int argc, char** argv);


    static GLUTWindow* instance;
    private:
};

}