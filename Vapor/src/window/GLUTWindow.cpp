#include "../../include/window/GLUTWindow.h"

namespace vpr {

GLUTWindow *GLUTWindow::instance = nullptr;
IWindowRenderer *GLUTWindow::windowRendererContext = nullptr;

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 */
void GLUTWindow::init(int argc, char** argv) {
    
    glutInit(&argc,argv);

    glutInitContextVersion(4, pgr::OGL_VER_MINOR);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutSetOption(GLUT_MULTISAMPLE, 8);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(this->size.width, this->size.height);
	glutCreateWindow("v a p o r - graphics engine");

    pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);


    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glClearColor(0.2f, 0.7f, 0.7f, 1.0f);
    glClearStencil(0);
    // glfwWindowHint(GLFW_SAMPLES, 4);
    
    glEnable(GL_MULTISAMPLE);  
    // glEnable(GL_MULTISAMPLE);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    glEnable(GL_BLEND);    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);  
    glFrontFace(GL_CW);  
    GLUTWindow::instance = this;

}

void GLUTWindow::displayLoop() {
    // GLUTWindow::windowRendererContext->loop();
}

void GLUTWindow::setLoopContext(IWindowRenderer* windowRenderer) {
    GLUTWindow::windowRendererContext = windowRenderer;
    glutDisplayFunc(GLUTWindow::displayLoop);

    
}



    
}