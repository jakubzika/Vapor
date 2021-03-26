#include "../../include/input/GLUTCallbackRegistry.h"

namespace vpr {

void GLUTCallbackRegistry::mountEventListeners() {
    glutMotionFunc(GLUTCallbackRegistry::onMouseMove);
    glutPassiveMotionFunc(GLUTCallbackRegistry::onMouseMove);
    glutKeyboardFunc(GLUTCallbackRegistry::onKeyboardEvent);
    glutMouseFunc((GLUTCallbackRegistry::onMousePress));

    GLUTCallbackRegistry::initialized = true;
}

void GLUTCallbackRegistry::setContext(GLUTInputsHandler* context) {
    if(!GLUTCallbackRegistry::initialized) GLUTCallbackRegistry::mountEventListeners();

    GLUTCallbackRegistry::context = context;
}

void GLUTCallbackRegistry::onKeyboardEvent(unsigned char key,int x, int y) {
    if(GLUTCallbackRegistry::context == nullptr) return;

    GLUTCallbackRegistry::context->onKeyboardEvent(key,x,y);
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

}