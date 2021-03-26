#pragma once

namespace vpr {

class GLUTInputsHandler {
    public:
    GLUTInputsHandler() {}

    virtual void onKeyboardEvent(unsigned char key,int x, int y){}
    virtual void onMouseMove(int x, int y){}
    virtual void onMousePress(int button, int state, int x, int y){}

};

// void GLUTInputsHandler::onKeyboardEvent(unsigned char key,int x, int y){}
// void GLUTInputsHandler::onMouseMove(int x, int y){}
// void GLUTInputsHandler::onMousePress(int button, int state, int x, int y){}x`

}

