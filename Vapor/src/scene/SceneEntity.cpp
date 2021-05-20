#include "../../include/scene/SceneEntity.h"

namespace vpr {

SceneEntity::SceneEntity() {
    this->visible = true;
}

void SceneEntity::generateRenderingData(SceneRenderingInstance& renderer){}
void SceneEntity::updatePositions(glm::mat4 model, glm::mat3 modelNormals, bool hidden){}

void SceneEntity::setParent(SceneEntity* parent) {
    this->parent = parent;
}

void SceneEntity::setPosition(glm::vec3 position) {
    this->position = position;
}
void SceneEntity::setRotation(glm::vec3 rotation) {
    this->rotation = rotation;
}   
void SceneEntity::setScale(glm::vec3 scale) {
    this->scale = scale;
}

void SceneEntity::setPosition(float x,float y,float z) {
    this->setPosition(glm::vec3(x,y,z));
}
void SceneEntity::setRotation(float x,float y,float z) {
    this->setRotation(glm::vec3(x,y,z));
}
void SceneEntity::setScale(float x,float y,float z) {
    this->setScale(glm::vec3(x,y,z));
}

glm::vec3 SceneEntity::getPosition() {
   return this->position;
}
glm::vec3 SceneEntity::getRotation() {
   return this->rotation;
}
glm::vec3 SceneEntity::getScale() {
   return this->scale;
}

}