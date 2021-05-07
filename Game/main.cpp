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

#include "include/engine/Engine.h"


#include "include/window/Window.h"
#include "include/window/GLUTWindow.h"

#include "include/action/UserCameraAction.h"
#include "include/action/EntityHovering.h"
#include "include/action/GLUTCaptureMouseSwitchAction.h"

struct state {
    vpr::Engine* engine;
} State;

float time_tick;

// void displayFunc() {
//     time_tick = time_tick + 1.0f;
    
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//     for(auto& column: *State.columns->getChildren()) 
//     {
//         column->setRotation(0.0,time_tick/10.0,0.0);
//     }

//     State.scene.updateData();
//     State.renderer.render();

//     glutSwapBuffers();

//     State.input->tick();
//     // CHECK_GL_ERROR();

// }

void addColumns(vpr::SceneNode* rootNode, vpr::MeshAsset *mesh, vpr::MaterialAsset* material) {

    for(int i = 0; i < 7; i++) {
        vpr::ModelEntity* columnModel = new vpr::ModelEntity(mesh,material);
        columnModel->setPosition(5.0,0.0,i*10.0);
        columnModel->setScale(0.05f,0.05f,0.05f);

        rootNode->addChild((columnModel));

        columnModel = new vpr::ModelEntity(mesh,material);
        columnModel->setPosition(-5.0,0.0,i*10.0);
        columnModel->setScale(0.05f,0.05f,0.05f);
        rootNode->addChild((columnModel));
        
    }
    
}

// void init(int argc, char** argv) {


//     vpr::Scene *scene = new vpr::Scene();
//     vpr::SceneCamera *camera = new vpr::SceneCamera();
//     vpr::SceneNode* root =new vpr::SceneNode();
//     vpr::SceneNode* columns =new vpr::SceneNode();
//     root->addChild(columns);

//     vpr::GLUTWindow* window = new vpr::GLUTWindow(1200,1200);
//     window->init(argc, argv);

//     vpr::UserInputHandler* input = new vpr::GLUTUserInputHandler(1200,1200);

//     vpr::MeshesHandler* meshesHandler = vpr::MeshesHandler::get_instance();
//     vpr::MaterialsHandler* materialsHandler = vpr::MaterialsHandler::get_instance();
    
//     vpr::MeshAsset* columnMesh = meshesHandler->loadFromFile("../../../Data/simple-mesh/simple-mesh.json");
//     vpr::MeshAsset* statueMesh = meshesHandler->loadFromFile("../../../Data/statue-mesh/statue-mesh.json");
//     vpr::MaterialAsset* simpleMaterial = materialsHandler->loadFromFile("../../../Data/simple-material/simple-material.json");

//     vpr::ModelEntity* statueModel = new vpr::ModelEntity(statueMesh, simpleMaterial);
//     statueModel->setPosition(0.0,0.0,70.0);
//     statueModel->setScale(0.2,0.2,0.2);
//     statueModel->setRotation(0.0,-0.4,0.0);
//     root->addChild(statueModel);

//     scene->setRoot(root);
//     camera->setWindowSize(1200,1200);
//     scene->setCamera(camera);
    
//     addColumns(columns, columnMesh, simpleMaterial);

//     camera->lookAt(glm::vec3(0.0,1.0,0.0),glm::vec3(0.0,0.0,20.0),glm::vec3(0.0,1.0,0.0));
    
//     State.engine = new vpr::Engine(scene,input, window);
    
    
//     State.engine->registerAction(new vpr::UserCameraAction(camera,input->getUserInput()));
//     State.engine->registerAction(new vpr::GLUTCaptureMouseSwitchAction(input->getUserInput(),1200,1200, input));
//     State.engine->registerAction(new vpr::EntityHovering(statueModel));
    
    
//     window->setLoopContext(State.engine);

    

// }

void onTimer(int) {
    glutPostRedisplay();
    glutTimerFunc(33, onTimer, 0);
}

// void screenResize(int width, int height) {
//     State.camera.setWindowSize(width,height);
//     State.camera.updateView();
//     // State.camera.updateProjection();
// }

int main(int argc, char** argv) {
    time_tick = 0.0f;

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    vpr::MeshesHandler* meshesHandler = vpr::MeshesHandler::get_instance();
    meshesHandler->setBasePath("../../../Data/meshes/");
    meshesHandler->setFileExtension(".obj");
    meshesHandler->loadAvailableAssets();

    // init(argc, argv);

    // State.engine->init();
    // State.engine->loop();

    // glutReshapeFunc(screenResize);
    // glutDisplayFunc(displayFunc);
    // glutTimerFunc(33,onTimer,0);

    // glutMainLoop();



    return 0;
}