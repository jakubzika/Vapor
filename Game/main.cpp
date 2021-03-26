#include <iostream>
#include <cmath>

#include "pgr.h"

#include "include/Types.h"
#include "include/assets/AssetHandler.h"
#include "include/hello.h"
#include "include/assets/MeshAsset.h"
#include "include/assets/MaterialAsset.h"
#include "include/assets/Asset.h"

#include "include/scene/Scene.h"
#include "include/scene/ModelEntity.h"
#include "include/scene/SceneNode.h"
#include "include/scene/SceneCamera.h"

#include "include/input/GLUTUserInput.h"
#include "include/input/UserInput.h"


struct state {
    vpr::Scene scene;
    vpr::SceneCamera camera;
    vpr::SceneRenderer renderer;
    vpr::SceneNode* columns;
    vpr::UserInputHandler* input;
} State;

float time_tick;

void displayFunc() {
    time_tick = time_tick + 1.0f;
    // CHECK_GL_ERROR();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // CHECK_GL_ERROR();


    // simpleMaterial->use();
    for(auto& column: *State.columns->getChildren()) 
    {
        column->setRotation(0.0,time_tick/10.0,0.0);
    }

    // State.camera.setPosition(glm::vec3(5.0,1.0,time_tick/1.0));
    // State.camera.setCenter(glm::vec3(5.0,0.0,time_tick/1.0+20.0));

    State.scene.updateData();

    // columnMesh->use();

    // glUniform1f(vpr::fixedUniformLocations["time"].location,time_tick);
    // glDrawElements(GL_TRIANGLES,columnMesh->numVertices,GL_UNSIGNED_INT,0);

    // // CHECK_GL_ERROR();
    // glBindVertexArray(0);
    State.renderer.render();


    glutSwapBuffers();
    // CHECK_GL_ERROR();

}

void addColumns(vpr::SceneNode* rootNode, vpr::MeshAsset *mesh, vpr::MaterialAsset* material) {

    for(int i =0; i < 10; i++) {
        vpr::ModelEntity* columnModel = new vpr::ModelEntity(mesh,material);
        columnModel->setPosition(10.0,0.0,i*10.0);
        columnModel->setScale(0.05f,0.05f,0.05f);

        rootNode->addChild((columnModel));

        columnModel = new vpr::ModelEntity(mesh,material);
        columnModel->setPosition(0.0,0.0,4.0+i*10.0);
        columnModel->setScale(0.05f,0.05f,0.05f);
        rootNode->addChild((columnModel));
        
    }
    
}

void init() {
    vpr::MeshesHandler* meshesHandler = vpr::MeshesHandler::get_instance();
    vpr::MaterialsHandler* materialsHandler = vpr::MaterialsHandler::get_instance();
    
    vpr::MeshAsset* columnMesh = meshesHandler->loadFromFile("../../../Data/simple-mesh/simple-mesh.json");
    vpr::MaterialAsset* simpleMaterial = materialsHandler->loadFromFile("../../../Data/simple-material/simple-material.json");

    vpr::ModelEntity* columnModel = new vpr::ModelEntity(columnMesh,simpleMaterial);
    vpr::SceneNode* rootNode = new vpr::SceneNode();


    State.scene.setRoot(rootNode);

    State.camera.setWindowSize(1600,1600);

    State.scene.setCamera(&State.camera);
    State.columns = rootNode;
    addColumns(rootNode, columnMesh, simpleMaterial);

    State.scene.gatherRenderingData(State.renderer);

    State.camera.lookAt(glm::vec3(5.0,1.0,0.0),glm::vec3(5.0,0.0,20.0),glm::vec3(0.0,1.0,0.0));
    // columnModel->setRotation(0,0,0);
    State.scene.updateData();

    State.input = new vpr::GLUTUserInputHandler();

}

void onTimer(int) {
    glutPostRedisplay();
    glutTimerFunc(33, onTimer, 0);
}

void screenResize(int width, int height) {
    State.camera.setWindowSize(width,height);
    State.camera.updateView();
    // State.camera.updateProjection();
}

int main(int argc, char** argv) {
    time_tick = 0.0f;
    glutInit(&argc, argv);

    glutInitContextVersion(4, pgr::OGL_VER_MINOR);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 1200);
	glutCreateWindow("shader toy");

    pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);

    CHECK_GL_ERROR();

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glClearColor(0.5f, 0.4f, 0.8f, 1.0f);


    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    

    CHECK_GL_ERROR();
    std::cout<<"initializing\n";
    init();
    std::cout<<"initialized\n";

    glutReshapeFunc(screenResize);
    glutDisplayFunc(displayFunc);
    glutTimerFunc(33,onTimer,0);

    glutMainLoop();



    return 0;
}