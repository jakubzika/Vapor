#include "../../include/action/RotatingLight.h"

#include <math.h>

namespace vpr {

RotatingLight::RotatingLight(SceneEntity* entity) {
    this->entity = entity;
    this->time = 0.0f;
    this->startingPosition = entity->getPosition();
}

void RotatingLight::tick(long msec) {
    this->time += 1.0;


    glm::vec3 position = glm::vec3(startingPosition);
    glm::vec3 rotation = entity->getRotation();


    rotation.x = sin(time*0.1)*10.0;
    rotation.z = cos(time*0.1)*10.0;
    // rotation.y = sin(time*0.1);

    entity->setRotation(glm::normalize(rotation));
}



}