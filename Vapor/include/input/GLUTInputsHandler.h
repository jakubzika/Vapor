/**
 * \file       .h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Interface for being passed as context to GLUTCallbackRegistry
 *
*/


#pragma once

namespace vpr {

class GLUTInputsHandler {
    public:
    GLUTInputsHandler() {}

    virtual void onKeyPress(unsigned char key,int x, int y){}
    virtual void onKeyUp(unsigned char key,int x, int y){}
    virtual void onSpecialKeyPress(int key,int x, int y){}
    virtual void onSpecialKeyUp(int key,int x, int y){}
    virtual void onMouseMove(int x, int y){}
    virtual void onMousePress(int button, int state, int x, int y){}



};

}

