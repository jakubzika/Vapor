#include "../../include/action/UserCameraAction.h"

namespace vpr {

UserCameraAction::UserCameraAction(SceneCamera* camera, UserInput* input, UserInputHandler* handler) {
    this->camera = camera;
    this->input = input;
    this->handler = handler;

    camera->setPosition(VIEW_STATIC_1_POSITION);
    camera->setCenter(VIEW_STATIC_1_CENTER);
    camera->setFOV(VIEW_STATIC_1_FOV);
    pitch = -2.4f;
    yaw = 42.0f;
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
    time++;
    

    bool cameraKeyPressed = false;
    if((this->input->keyPressed[VPR_KEY_C] && this->input->deltaKeyPressed[VPR_KEY_C])) {
        // this->handler->setLockedCursor(true);
        cameraKeyPressed = true;
           
    }
    auto center = camera->getCenter();
    auto position = camera->getPosition();
    glm::vec3 newPosition, newCenter;
    bool shouldMove = false;


    float x;
    float y;

    switch(activeView) {
        case VIEW_STATIC_1:
        if(cameraKeyPressed) {
            std::cout << "Switching camera to VIEW_STATIC_2\n";
            activeView = VIEW_STATIC_2;
            camera->setPosition(VIEW_STATIC_2_POSITION);
            camera->setCenter(VIEW_STATIC_2_CENTER);
            camera->setFOV(VIEW_STATIC_2_FOV);
        }
        break;
        case VIEW_STATIC_2:
            if(cameraKeyPressed) {
                std::cout << "Switching camera to VIEW_FREE\n";
                activeView = VIEW_FREE;
                camera->setPosition(freeViewCameraPosition);
                camera->setCenter(freeViewCameraCenter);
                camera->setFOV(VIEW_FREE_FOV);
                handler->setLockedCursor(true);
            }
        break;
        case VIEW_FREE:
            // std::cout << camera->getPosition().x << "f, " << camera->getPosition().y << "f, " << camera->getPosition().z << "f, - ";
            // std::cout << camera->getCenter().x << "f, " << camera->getCenter().y << "f, " << camera->getCenter().z << "f, " << std::endl;

            if(cameraKeyPressed) {
                std::cout << "Switching camera to VIEW_ROTATING\n";
                activeView = VIEW_ROTATING;
                freeViewCameraPosition = camera->getPosition();
                freeViewCameraCenter = camera->getCenter();

                camera->setCenter(VIEW_ROTATING_INITIAL_CENTER);
                camera->setFOV(VIEW_ROTATING_FOV);
                handler->setLockedCursor(false);
                break;
            }

            if(input->keyPressed[VPR_KEY_W]) {
                newPosition = position + (this->direction*CAMERA_SPEED);
                newCenter = center + (this->direction*CAMERA_SPEED);
                shouldMove = true;
            } else if(input->keyPressed[VPR_KEY_S]) {
                newPosition = position - (this->direction*CAMERA_SPEED);
                newCenter = center - (this->direction*CAMERA_SPEED);
                shouldMove = true;
            }
            // std::cout << "distance from center " << glm::distance(newPosition, glm::vec3(0.0,0.0,0.0)) << std::endl;
            if(shouldMove  && glm::distance(newPosition, glm::vec3(0.0,0.0,0.0)) < MAX_CAMERA_DISTANCE) {
                this->camera->setPosition(newPosition);
                this->camera->setCenter(newCenter);
            }
            this->handleMouse();


        break;
        case VIEW_ROTATING:
            if(cameraKeyPressed) {
                std::cout << "Switching camera to VIEW_STATIC_1\n";
                activeView = VIEW_STATIC_1;
                freeViewCameraPosition = camera->getPosition();
                freeViewCameraCenter = camera->getCenter();


                camera->setPosition(VIEW_STATIC_1_POSITION);
                camera->setCenter(VIEW_STATIC_1_CENTER);
                camera->setFOV(VIEW_STATIC_1_FOV);
                handler->setLockedCursor(false);
                break;
            }
            x = sin(((float)time)/80.0f) * 10.0f;
            y = cos(((float)time)/80.0f) * 10.0f;

            camera->setPosition(glm::vec3(x,4.0f,y));

        break;
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
    this->handleKeyboard();
}

bool UserCameraAction::isFinished() {
    return false;
}

}