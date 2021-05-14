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
#include "include/scene/LightEntity.h"  

#include "include/input/GLUTUserInput.h"
#include "include/input/UserInput.h"

#include "include/engine/Engine.h"


#include "include/window/Window.h"
#include "include/window/GLUTWindow.h"

#include "include/action/UserCameraAction.h"
#include "include/action/EntityHovering.h"
#include "include/action/GLUTCaptureMouseSwitchAction.h"
#include "include/action/RotatingLight.h"

#include "include/gl/LightsUBO.h"

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

// void addColumns(vpr::SceneNode* rootNode, vpr::MeshAsset *mesh, vpr::MaterialAsset* material) {

//     for(int i = 0; i < 7; i++) {
//         vpr::ModelEntity* columnModel = new vpr::ModelEntity(mesh,material);
//         columnModel->setPosition(5.0,0.0,i*10.0);
//         columnModel->setScale(0.05f,0.05f,0.05f);

//         rootNode->addChild((columnModel));

//         columnModel = new vpr::ModelEntity(mesh,material);
//         columnModel->setPosition(-5.0,0.0,i*10.0);
//         columnModel->setScale(0.05f,0.05f,0.05f);
//         rootNode->addChild((columnModel));
        
//     }
    
// }

void init(int argc, char** argv) {

    
    vpr::Scene *scene = new vpr::Scene();
    vpr::SceneCamera *camera = new vpr::SceneCamera();
    vpr::SceneNode* root =new vpr::SceneNode();
    // vpr::SceneNode* columns =new vpr::SceneNode();
    // root->addChild(columns);

    vpr::GLUTWindow* window = new vpr::GLUTWindow(1200,1200);
    window->init(argc, argv);

    vpr::UserInputHandler* input = new vpr::GLUTUserInputHandler(1200,1200);

    vpr::MeshesHandler* meshesHandler = vpr::MeshesHandler::get_instance();
    vpr::MaterialsHandler* materialsHandler = vpr::MaterialsHandler::get_instance();

    vpr::ModelEntity* terrainModel = new vpr::ModelEntity("terrain","terrain");
    // vpr::ModelEntity* columnModel = new vpr::ModelEntity("column","marble");

    vpr::ModelEntity* statueModel = new vpr::ModelEntity("statue","marble");


    terrainModel->setPosition(0.0,0.0,4.0);
    terrainModel->setScale(1.0,1.0,1.0);

    vpr::LightEntity* sunLight = new vpr::LightEntity(vpr::LIGHT_SUN);
    sunLight->setRotation(0.0,0.0,-1.0);
    sunLight->setStrength(5.0);


    // terrainModel->setRotation(0.0,-0.4,0.0);
    statueModel->setPosition(4.0,0.0,0.0);
    statueModel->setScale(0.1,0.1,0.1);



    root->addChild(terrainModel);
    root->addChild(sunLight);
    root->addChild(statueModel);
    scene->setRoot(root);
    camera->setWindowSize(1200,1200);
    scene->setCamera(camera);
    camera->lookAt(glm::vec3(0.0,1.0,0.0),glm::vec3(0.0,0.0,20.0),glm::vec3(0.0,1.0,0.0));

    
    // State.engine->registerAction(new vpr::EntityHovering(statueModel));

    State.engine = new vpr::Engine(scene,input, window);
    window->setLoopContext(State.engine);

    State.engine->registerAction(new vpr::UserCameraAction(camera,input->getUserInput()));
    State.engine->registerAction(new vpr::GLUTCaptureMouseSwitchAction(input->getUserInput(),1200,1200, input));
    // State.engine->registerAction(new vpr::EntityHovering(sunLight));
    State.engine->registerAction(new vpr::EntityHovering(statueModel));
    // State.engine->registerAction(new vpr::RotatingLight(sunLight));

    // vpr::MeshAsset* columnMesh = meshesHandler->loadFromFile("../../../Data/simple-mesh/simple-mesh.json");
    // vpr::MeshAsset* statueMesh = meshesHandler->loadFromFile("../../../Data/statue-mesh/statue-mesh.json");
    // vpr::MaterialAsset* simpleMaterial = materialsHandler->loadFromFile("../../../Data/simple-material/simple-material.json");

    // vpr::ModelEntity* statueModel = new vpr::ModelEntity(statueMesh, simpleMaterial);
    // statueModel->setPosition(0.0,0.0,70.0);
    // statueModel->setScale(0.2,0.2,0.2);
    // statueModel->setRotation(0.0,-0.4,0.0);
    // root->addChild(statueModel);

    // scene->setRoot(root);
    // camera->setWindowSize(1200,1200);
    // scene->setCamera(camera);
    
    // addColumns(columns, columnMesh, simpleMaterial);

    
}

void onTimer(int) {
    glutPostRedisplay();
    glutTimerFunc(33, onTimer, 0);
}

// void screenResize(int width, int height) {
//     State.camera.setWindowSize(width,height);
//     State.camera.updateView();
//     // State.camera.updateProjection();
// }

void handlersInit() {
    vpr::MeshesHandler* meshesHandler = vpr::MeshesHandler::get_instance();
    meshesHandler->setBasePath("../../../Data/meshes/");
    meshesHandler->setFileExtension(".json");
    meshesHandler->loadAvailableAssets();

    vpr::MaterialsHandler* materialsHandler = vpr::MaterialsHandler::get_instance();
    materialsHandler->setBasePath("../../../Data/materials/");
    materialsHandler->setFileExtension(".json");
    materialsHandler->loadAvailableAssets();

    vpr::ShadersHandler* shadersHandler = vpr::ShadersHandler::get_instance();
    shadersHandler->setBasePath("../../../Data/shaders/");
    shadersHandler->setFileExtension(".json");
    shadersHandler->loadAvailableAssets();

    vpr::TexturesHandler* texturesHandler = vpr::TexturesHandler::get_instance();
    texturesHandler->setBasePath("../../../Data/textures/");
    texturesHandler->setFileExtension(".json");
    texturesHandler->loadAvailableAssets();
}

int main(int argc, char** argv) {
    time_tick = 0.0f;

    handlersInit();
    init(argc, argv);


    State.engine->init();
    State.engine->loop();

    // glutReshapeFunc(screenResize);
    // glutDisplayFunc(displayFunc);
    // glutTimerFunc(33,onTimer,0);

    glutMainLoop();



    return 0;
}