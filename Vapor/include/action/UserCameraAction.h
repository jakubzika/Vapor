#pragma once

#include <iostream>

#include "IAction.h"

#include "../scene/SceneCamera.h"
#include "../input/UserInput.h"

namespace vpr {

enum Views {
    VIEW_STATIC_1,
    VIEW_STATIC_2,
    VIEW_ROTATING,
    VIEW_FREE,
};

#define VIEW_STATIC_1_POSITION glm::vec3(8.3554f, 2.97861f, -6.34368f)
#define VIEW_STATIC_1_CENTER glm::vec3( 7.57823f, 2.79809f, -5.74084f)
#define VIEW_STATIC_1_FOV 45.0f

#define VIEW_STATIC_2_POSITION glm::vec3(6.23059f, 0.422824f, 0.0265828f)
#define VIEW_STATIC_2_CENTER glm::vec3( 5.24657f, 0.599909f, 0.00768885f)
#define VIEW_STATIC_2_FOV 50.0f

#define VIEW_FREE_INITIAL_POSITION glm::vec3(-1.28239f, 0.943196f, -2.1309f)
#define VIEW_FREE_INITIAL_CENTER glm::vec3(-0.472138f, 0.859518f, -1.55082f)
#define VIEW_FREE_FOV 60.0f


#define VIEW_ROTATING_FOV 50.0f
#define VIEW_ROTATING_INITIAL_CENTER glm::vec3(0.0f,0.0f,0.0f)


#define MAX_CAMERA_DISTANCE 15.0f
#define CAMERA_SPEED 0.17f

class UserCameraAction: public IAction {

    public:
    UserCameraAction(SceneCamera* camera, UserInput* input,UserInputHandler* handler);
    bool isFinished();
    void tick(long msec);

    private:
    void handleMouse();
    void handleKeyboard();


    glm::vec3 direction{0.0,0.0,0.0};
    float pitch{0};
    float yaw{0};

    SceneCamera* camera;
    UserInput* input;
    UserInputHandler* handler;
    unsigned long time{0};

    Views activeView{VIEW_STATIC_1};

    glm::vec3 freeViewCameraPosition{VIEW_FREE_INITIAL_POSITION};
    glm::vec3 freeViewCameraCenter{VIEW_FREE_INITIAL_CENTER};

};

}