#include "../../include/scene/Scene.h"

namespace vpr {

Scene::Scene() {

}

Scene::~Scene() {
    for(auto& object : this->objects)
    {
        delete object;
    }
    this->objects.clear();
}

void Scene::gatherRenderingData(SceneRenderingInstance& renderer) {

    renderer.beforeGather();
    renderer.setCamera(this->camera->getCameraData());
    if(this->root != nullptr) {
        this->root->generateRenderingData(renderer);
    }
    if(skybox != nullptr) {
        auto skyboxData = skybox->getData();
        renderer.setSkybox(std::get<0>(skyboxData),std::get<1>(skyboxData),std::get<2>(skyboxData));
    }
    renderer.afterGather();
}

void Scene::updateData(SceneRenderingInstance& renderer) {
    renderer.setCamera(this->camera->getCameraData());

    renderer.beforeDataUpdate();
    if(this->root != nullptr) {

        glm::mat4 matrixRoot(1.0);
        glm::mat3 normalMatrixRoot(1.0);
        this->root->updatePositions(matrixRoot,normalMatrixRoot, false);
    }

    if(this->camera != nullptr) {
        this->camera->updateView();
        this->camera->updateProjection();
    }
    renderer.afterDataUpdate();
}

void Scene::setRoot(SceneEntity* root) {
    this->root = root;
}

SceneEntity* Scene::getRoot() {
    return this->root;
}


void Scene::setCamera(SceneCamera* camera) {
    this->camera = camera;
}

void Scene::setSkybox(ModelEntity* skybox) {
    this->skybox = skybox;
}

}