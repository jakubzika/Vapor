#pragma once

namespace vpr {

struct WindowSize {
    int width;
    int height;
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