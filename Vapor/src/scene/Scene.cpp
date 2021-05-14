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
    renderer.afterGather();
}

void Scene::updateData(SceneRenderingInstance& renderer) {
    renderer.beforeDataUpdate();
    if(this->root != nullptr) {

        glm::mat4 matrixRoot(1.0);
        glm::mat3 normalMatrixRoot(1.0);
        this->root->updatePositions(matrixRoot,normalMatrixRoot);
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

}