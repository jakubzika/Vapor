#include "../../include/input/GLUTCallbackRegistry.h"

namespace vpr {

void GLUTCallbackRegistry::mountEventListeners() {
    glutMotionFunc(GLUTCallbackRegistry::onMouseMove);
    glutPassiveMotionFunc(GLUTCallbackRegistry::onMouseMove);
    glutKeyboardFunc(GLUTCallbackRegistry::onKeyPress);
    glutKeyboardUpFunc(GLUTCallbackRegistry::onKeyUp);
    glutSpecialFunc(GLUTCallbackRegistry::onSpecialKeyPress);
    glutSpecialUpFunc(GLUTCallbackRegistry::onSpecialKeyUp);
    glutMouseFunc((GLUTCallbackRegistry::onMousePress));

    GLUTCallbackRegistry::initialized = true;
}

void GLUTCallbackRegistry::setContext(GLUTInputsHandler* context) {
    if(!GLUTCallbackRegistry::initialized) GLUTCallbackRegistry::mountEventListeners();

    GLUTCallbackRegistry::context = context;
}

void GLUTCallbackRegistry::onKeyPress(unsigned char key,int x, int y) {
    if(GLUTCallbackRegistry::context == nullptr) return;

    GLUTCallbackRegistry::context->onKeyPress(key,x,y);
}

void GLUTCallbackRegistry::onKeyUp(unsigned char key,int x, int y) {
    if(GLUTCallbackRegistry::context == nullptr) return;

    GLUTCallbackRegistry::context->onKeyUp(key,x,y);
}

void GLUTCallbackRegistry::onSpecialKeyPress(int key,int x, int y) {
    if(GLUTCallbackRegistry::context == nullptr) return;

    GLUTCallbackRegistry::context->onSpecialKeyPress(key,x,y);
}

void GLUTCallbackRegistry::onSpecialKeyUp(int key,int x, int y) {
    if(GLUTCallbackRegistry::context == nullptr) return;

    GLUTCallbackRegistry::context->onSpecialKeyUp(key,x,y);
}

void GLUTCallbackRegistry::onMouseMove(int x, int y) {
    if(GLUTCallbackRegistry::context == nullptr) return;

    GLUTCallbackRegistry::context->onMouseMove(x,y);
}

void GLUTCallbackRegistry::onMousePress(int button, int state, int x, int y) {
    if(GLUTCallbackRegistry::context == nullptr) return;

    GLUTCallbackRegistry::context->onMousePress(button,state,x,y);
}

bool GLUTCallbackRegistry::initialized = false;
GLUTInputsHandler *GLUTCallbackRegistry::context = nullptr;

}