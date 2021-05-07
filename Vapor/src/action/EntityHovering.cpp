#include "../../include/action/EntityHovering.h"

namespace vpr {

EntityHovering::EntityHovering(SceneEntity* entity) {
    this->entity = entity;
    this->time = 0.0f;
    this->startingPosition = entity->getPosition();
}

void EntityHovering::tick(long msec) {
    this->time += 1.0;


    glm::vec3 position = glm::vec3(startingPosition);
    glm::vec3 rotation = entity->getRotation();


    position.y += sin(time*0.02)*1.0+10.0;
    rotation.y += 0.04;

    entity->setPosition(position);
    entity->setRotation(rotation);
}



}