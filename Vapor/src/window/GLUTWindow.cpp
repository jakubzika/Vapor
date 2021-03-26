#include "../../include/window/GLUTWindow.h"

namespace vpr {

GLUTWindow *GLUTWindow::instance = nullptr;

void GLUTWindow::init(int argc, char** argv) {
    
    glutInit(&argc,argv);

    glutInitContextVersion(4, pgr::OGL_VER_MINOR);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(this->size.width, this->size.height);
	glutCreateWindow("v a p o r - graphics engine");

    pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);


    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glClearColor(0.5f, 0.4f, 0.8f, 1.0f);
}
    
}