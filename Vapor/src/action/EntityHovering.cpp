#include "../../include/action/EntityHovering.h"

namespace vpr {

EntityHovering::EntityHovering(SceneEntity* entity) {
    this->entity = entity;
    this->time = 0.0f;
    this->startingPosition = entity->getPosition();
}

void EntityHovering::tick(long msec) {
    if(!enabled) return;

    this->time += 1.0;


    glm::vec3 position = glm::vec3(startingPosition);
    glm::vec3 rotation = entity->getRotation();


    position.y += sin(time*0.02)*0.07;
    rotation.y += 0.01;
    rotation.x += 0.01;
    rotation.z += 0.01;

    entity->setPosition(position);
    entity->setRotation(rotation);
}

void EntityHovering::setEnabled(bool enabled) {
    this->enabled = enabled;
    // if(!enabled) entity->setPosition(startingPosition);
}


}