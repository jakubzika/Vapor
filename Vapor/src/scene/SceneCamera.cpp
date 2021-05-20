#include "../../include/scene/SceneCamera.h"
#include <iostream>

namespace vpr {

SceneCamera::SceneCamera() {

}

void SceneCamera::lookAt(glm::vec3 position,glm::vec3 center,glm::vec3 up) {
    this->position = position;
    this->center = center;
    this->up = up;
}

void SceneCamera::updateView() {
    glm::mat4 view = glm::lookAt(this->position, this->center, this->up);

    this->data.view = view;

}

void SceneCamera::updateProjection() {
    glm::mat4 proj = glm::perspective(glm::radians(this->FOV), (float)this->width/(float)this->height, 0.1f, 5000.0f);

    this->data.projection = proj;

}

void SceneCamera::setPosition(glm::vec3 position) {
    this->position = position;
}

void SceneCamera::setCenter(glm::vec3 center) {
    this->center = center;
}

void SceneCamera::setUp(glm::vec3 up) {
    this->up = up;
}

void SceneCamera::setCamera(glm::vec3 position ,glm::vec3 center, glm::vec3 up) {
    this->position = position;
    this->center = center;
    this->up = up;
}

void SceneCamera::setWindowSize(int width,int height) {
    this->width = width;
    this->height = height;
}

void SceneCamera::setFOV(float FOV) {
    this->FOV = FOV;
}

CameraData* SceneCamera::getCameraData() {
    // std::cout << " cam: " <<center.x << " " << center.y << " " << center.z << "\n";
    this->data.position = position;
    return &this->data;
}



}