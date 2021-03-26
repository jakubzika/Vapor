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
    renderer.setCamera(this->camera->getCameraData());
    if(this->root != nullptr) {
        this->root->generateRenderingData(renderer);
    }
}

void Scene::updateData() {
    if(this->root != nullptr) {

        glm::mat4 matrixRoot(1.0);
        this->root->updatePositions(matrixRoot,matrixRoot);
    }

    if(this->camera != nullptr) {
        this->camera->updateView();
        this->camera->updateProjection();
    }
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