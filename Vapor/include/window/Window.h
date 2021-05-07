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