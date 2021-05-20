#include <iostream>
#include <cmath>

#include "pgr.h"

#include "include/Vapor.h"

using namespace zikajak3;

struct state {
    vpr::Engine* engine;
} State;

float time_tick;

void loadHardcodedModels() {
    vpr::MeshesHandler* meshesHandler = vpr::MeshesHandler::get_instance();

    vpr::MeshAsset* cubeMesh = new vpr::MeshAsset();
    cubeMesh->loadFromBuffer(vpr::models::cubeNAttribsPerVertex, vpr::models::cubeNVertices, vpr::models::cubeNTriangles, vpr::models::cubeVertices, vpr::models::cubeTriangles);
    meshesHandler->addAssetManually(cubeMesh, "unit-cube");

    vpr::MeshAsset* pedestalMesh = new vpr::MeshAsset();
    pedestalMesh->loadFromBuffer(vpr::models::pedestalNAttribsPerVertex, vpr::models::pedestalNVertices, vpr::models::pedestalNTriangles, vpr::models::pedestalVertices, vpr::models::pedestalTriangles);
    meshesHandler->addAssetManually(pedestalMesh, "pedestal");
}

void init(int argc, char** argv) {

    
    vpr::Scene *scene = new vpr::Scene();
    vpr::SceneCamera *camera = new vpr::SceneCamera();
    vpr::SceneNode* root =new vpr::SceneNode();

    vpr::GLUTWindow* window = new vpr::GLUTWindow(WINDOW_WIDTH,WINDOW_HEIGHT);
    window->init(argc, argv);

    loadHardcodedModels();

    vpr::UserInputHandler* input = new vpr::GLUTUserInputHandler(WINDOW_WIDTH,WINDOW_HEIGHT);


    vpr::ModelEntity* terrainModel = new vpr::ModelEntity("terrain-circle","terrain-circle");
    terrainModel->setPosition(10.34,0.42,-3.14);
    vpr::ModelEntity* bathhouseModel = new vpr::ModelEntity("bathhouse","marble");
    vpr::ModelEntity* statueModel = new vpr::ModelEntity("statue","floor");
    statueModel->setSelectable(true);

    vpr::ModelEntity* planeModel = new vpr::ModelEntity("plane", "uv");
    vpr::ModelEntity* skyboxModel = new vpr::ModelEntity("unit-cube", "skybox");
    vpr::ModelEntity* waterModel = new vpr::ModelEntity("bathhouse-water-level", "water");
    vpr::ModelEntity* cylinderModel = new vpr::ModelEntity("cylinder", "terrain-circle");

    vpr::SceneNode* bathhouse = new vpr::SceneNode();
    vpr::SceneNode* waterFlowA = new vpr::SceneNode();
    vpr::SceneNode* waterFlowB = new vpr::SceneNode();
    vpr::SceneNode* waterLevelAnimation = new vpr::SceneNode();
    vpr::SceneNode* waterLevel = new vpr::SceneNode();
    vpr::SceneNode* waterFlow = new vpr::SceneNode();
    vpr::SceneNode* waterSplash = new vpr::SceneNode();


    waterModel->setPosition(-0.1361,0.0,-0.0464);
    waterFlowA->setPosition(-0.2187,0.056,0.499);
    waterFlowB->setPosition(0.0557,0.056,-0.642);

    waterFlow->addChild(waterFlowA);
    waterFlow->addChild(waterFlowB);
    
    bathhouse->addChild(waterFlow);
    bathhouse->addChild(cylinderModel);
    cylinderModel->setRotation(0.0,0.0,0.0);
    cylinderModel->setPosition(0.0,0.0,-0.18);
    // bathhouse->addChild(waterFlow);

    for(int i = 0; i < 3; i++){
        float offset = 0.142;
        vpr::ModelEntity* waterFlowModel = new vpr::ModelEntity("bathhouse-water-flow","water-flow");
        vpr::ModelEntity* waterSplashModel = new vpr::ModelEntity("bathhouse-water-splash","water-splash");

        waterFlowModel->setPosition(i*offset,0.0,0.0);
        waterFlowModel->setRotation(0.0,3.14,0.0);

        waterSplashModel->setPosition(-0.219-i*offset,0.001,0.459);

        waterFlowA->addChild(waterFlowModel);
        
        waterSplash->addChild(waterSplashModel);
    }

    waterLevel->setPosition(0.0,-0.166,0.0);
    waterLevel->addChild(waterModel);

    for(int i =0; i < 5; i++){
        vpr::ModelEntity* waterModelTransparent = new vpr::ModelEntity("bathhouse-water-level", "water-transparent");
        waterModelTransparent->setPosition(0.0,0.01 + 0.005*i,0.0);
        waterLevel->addChild(waterModelTransparent);

    }

    waterLevel->addChild(waterLevelAnimation); 
    bathhouse->addChild(waterLevel);

    

    for(int i = 0; i < 3; i++){
        float offset = 0.142;
        vpr::ModelEntity* waterFlowModel = new vpr::ModelEntity("bathhouse-water-flow","water-flow");
        vpr::ModelEntity* waterSplashModel = new vpr::ModelEntity("bathhouse-water-splash","water-splash");

        waterFlowModel->setPosition(-i*offset,0.0,0.0);
        waterSplashModel->setPosition(0.056+i*offset,0.001,-0.6124);

        waterFlowB->addChild(waterFlowModel);
        waterSplash->addChild(waterSplashModel);

    }

    bathhouse->setPosition(0.0,0.4,0.0);
    {
        vpr::ModelEntity* floorModel = new vpr::ModelEntity("bathhouse-floor", "floor");
        floorModel->setPosition(-0.066,0.0,-0.069);
        bathhouse->addChild(floorModel);

        vpr::ModelEntity* roofModel = new vpr::ModelEntity("bathhouse-roof", "roof");
        roofModel->setPosition(-0.092,0.698,-0.0656);
        bathhouse->addChild(roofModel);

        for(int i = 0; i < 7; i++){

            vpr::ModelEntity* columnModel = new vpr::ModelEntity("column", "column");
            columnModel->setPosition(-1.404 + i*0.43,-0.005,0.634);
            bathhouse->addChild(columnModel);

            columnModel = new vpr::ModelEntity("column", "column");
            columnModel->setPosition(-1.404 + i*0.43,-0.005,-0.766);
            bathhouse->addChild(columnModel);

        }

        {
            vpr::ModelEntity* columnModel;

            columnModel = new vpr::ModelEntity("column", "column");
            bathhouse->addChild(columnModel);
            columnModel->setPosition(1.25,-0.005,-0.3724);
            
            columnModel = new vpr::ModelEntity("column", "column");
            bathhouse->addChild(columnModel);
            columnModel->setPosition(1.25,-0.005,0.34);


            columnModel = new vpr::ModelEntity("column", "column");
            bathhouse->addChild(columnModel);
            columnModel->setPosition(-1.4,-0.005,-0.3724);
            
            columnModel = new vpr::ModelEntity("column", "column");
            bathhouse->addChild(columnModel);
            columnModel->setPosition(-1.4,-0.005,0.34);

        }

        for(int i =0; i < 3; i++) {
            vpr::LightEntity* pointLight = new vpr::LightEntity(vpr::LIGHT_POINT);
            pointLight->setAttentuation(1.0,0.6,0.6);
            pointLight->setPosition(-2.408+i*1.8,0.572,-0.065);
            pointLight->setColor(0.749, 0.6706, 0.8157);
            bathhouse->addChild(pointLight);
        }

        {
            vpr::ModelEntity* stairsModel = new vpr::ModelEntity("stairs", "floor");
            stairsModel->setPosition(2.3,0.02,0.0);
            bathhouse->addChild(stairsModel);

        }
    }

    vpr::SceneNode* icoSphere = new vpr::SceneNode();
    {
        vpr::ModelEntity* icoSphereModel = new vpr::ModelEntity("ico-sphere","gold");

        vpr::LightEntity* icoSphereLight = new vpr::LightEntity(vpr::LIGHT_POINT);
        icoSphereLight->setColor(0.9216, 0.7922, 0.2784);
        icoSphereLight->setAttentuation(1.0,0.35,0.44);
        
        icoSphere->setPosition(0.0,0.36,0.0);
        icoSphere->addChild(icoSphereModel);
        icoSphere->addChild(icoSphereLight);

        vpr::ModelEntity* starModel = new vpr::ModelEntity("star", "star-animation");
        icoSphere->addChild(starModel);
        starModel->setScale(2.0,2.0,2.0);
        starModel = new vpr::ModelEntity("star", "star-animation");
        starModel->setRotation(0.0,3.14/2.0,0.0);
        starModel->setScale(2.0,2.0,2.0);
        icoSphere->addChild(starModel);

        starModel = new vpr::ModelEntity("star", "star-animation");
        starModel->setRotation(0.0,0.0,3.14/2);
        starModel->setScale(2.0,2.0,2.0);
        icoSphere->addChild(starModel);

        bathhouse->addChild(icoSphere);
    }

    vpr::ModelEntity* valveModel = new vpr::ModelEntity("valve","valve");
    {
        valveModel->setPosition(-0.085,0.094,-0.942);
        valveModel->setRotation(0.0,3.14,0.0);
        valveModel->setSelectable(true);
        bathhouse->addChild(valveModel);
    }

    float baseY = 0.3;
    std::vector<std::tuple<glm::vec3,glm::vec3>> treePositions = {
        std::make_tuple(glm::vec3(1.326,baseY,-1.34),glm::vec3(1.0,1.0,1.0)),
        std::make_tuple(glm::vec3(-1.36,baseY,-1.28),glm::vec3(1.2,1.2,1.2)),
        std::make_tuple(glm::vec3(-0.122,baseY,1.61),glm::vec3(1.0,1.0,1.0)),
        std::make_tuple(glm::vec3(1.09,baseY,1.5),glm::vec3(1.0,1.0,1.0)),
        };
    
    for(int i = 0; i < treePositions.size(); i++){
        vpr::SceneNode* tree = new vpr::SceneNode();
        vpr::ModelEntity* treeModel = new vpr::ModelEntity("tree", "tree");
        tree->setPosition(std::get<0>(treePositions[i]));
        tree->setScale(std::get<1>(treePositions[i]));


        vpr::ModelEntity* leavesModel = new vpr::ModelEntity("leaves", "tree");

        tree->addChild(treeModel);
        tree->addChild(leavesModel);
        root->addChild(tree);
    }
    
    vpr::LightEntity* sunLight = new vpr::LightEntity(vpr::LIGHT_SUN);
    sunLight->setRotation(-0.5f,-0.5f,0.2f);
    sunLight->setStrength(1.0f);
    sunLight->setColor(1.0,1.0,1.0);

    vpr::LightEntity* pointLight = new vpr::LightEntity(vpr::LIGHT_POINT);
    pointLight->setPosition(0.0,0.6,0.0);
    pointLight->setAttentuation(1.0,0.2,0.2);

    vpr::LightEntity* spotLight = new vpr::LightEntity(vpr::LIGHT_SPOT);
    spotLight->setPosition(0.236,1.865,-1.55);
    spotLight->setColor(1.0,1.0,1.0);
    spotLight->setCone(0.96,0.82);
    spotLight->setRotation(0.0,-1.0,0.0);
    root->addChild(spotLight);
    statueModel->setPosition(0.26,0.3,-1.554);
    statueModel->setRotation(0.0,-3.14/2,0.0);


    bathhouseModel->setPosition(-1.5,0.1,-4.5);
    bathhouseModel->setScale(0.1,0.1,0.1);

    planeModel->setPosition(0.0,-1.2,0.0);
    root->addChild(bathhouse);
    root->addChild(sunLight);
    root->addChild(statueModel);
    scene->setRoot(root);
    camera->setWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    scene->setCamera(camera);
    scene->setSkybox(skyboxModel);
    camera->lookAt(glm::vec3(0.0,1.0,0.0),glm::vec3(0.0,0.0,20.0),glm::vec3(0.0,1.0,0.0));

    vpr::TextureAsset* skybox = vpr::TexturesHandler::get_instance()->getAsset("skybox");
    

    State.engine = new vpr::Engine(scene,input, window);
    window->setLoopContext(State.engine);

    State.engine->registerAction(new vpr::UserCameraAction(camera,input->getUserInput(), input));
    State.engine->registerAction(new vpr::GLUTCaptureMouseSwitchAction(input->getUserInput(),WINDOW_WIDTH,WINDOW_HEIGHT, input));
    auto hovering = new vpr::EntityHovering(statueModel);
    State.engine->registerAction(new vpr::SelectableItems(input->getUserInput(), State.engine->getRenderer(),valveModel,{waterFlow, waterSplash},waterLevel));
    State.engine->registerAction(new vpr::UserKeyAction(input->getUserInput()));
    State.engine->registerAction(new vpr::EntityHovering(icoSphere));


}

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
    glutMainLoop();



    return 0;
}