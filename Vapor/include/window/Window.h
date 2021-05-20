/**
 * \file       Window.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Base description for window
 *
*/

#pragma once

namespace vpr {

struct WindowSize {
    int width;
    int height;
};


class IWindowRenderer {
    public:
    virtual void loop() = 0;
};

class Window {
    public:

    Window(int width, int height);
    WindowSize getWindowSize();
    
    
    //virtual ~Window();

    protected:
    WindowSize size;
};

}