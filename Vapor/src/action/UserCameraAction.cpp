#include "../../include/action/UserCameraAction.h"

namespace vpr {

UserCameraAction::UserCameraAction(SceneCamera* camera, UserInput* input) {
    this->camera = camera;
    this->input = input;
}

void UserCameraAction::handleMouse() {
    if(!input->mouseLocked || (input->deltaMouseX == 0 && input->deltaMouseY == 0)) return;

    int deltaX = input->deltaMouseX;
    int deltaY = input->deltaMouseY;

    pitch -= deltaY * 0.1f;
    yaw += deltaX * 0.1f;

    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    
    this->direction.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
    this->direction.y = sin(glm::radians(pitch));
    this->direction.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
    
    this->camera->setCenter(this->camera->getPosition() + glm::normalize(direction));
}

void UserCameraAction::handleKeyboard() {
    auto center = camera->getCenter();
    auto position = camera->getPosition();
    


    if(input->keyPressed[VPR_KEY_W]) {
        camera->setPosition(position + (this->direction*0.2f));
        camera->setCenter(center + (this->direction*0.2f));
    } else if(input->keyPressed[VPR_KEY_S]) {
        camera->setPosition(position - (this->direction*0.2f));
        camera->setCenter(center - (this->direction*0.2f));
    }

    // if(input->keyPressed[VPR_KEY_A]) {
    //     center.x += 0.5;
    //     position.x += 0.5;
    // } else if(input->keyPressed[VPR_KEY_D]) {
    //     center.x -= 0.5;
    //     position.x -= 0.5;
    // }
    // camera->setPosition(position);
    // camera->setCenter(center);
}




void UserCameraAction::tick(long msec) {
    this->handleMouse();
    this->handleKeyboard();
}

bool UserCameraAction::isFinished() {
    return false;
}

}