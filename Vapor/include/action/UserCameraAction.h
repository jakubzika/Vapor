#pragma once

#include <iostream>

#include "IAction.h"

#include "../scene/SceneCamera.h"
#include "../input/UserInput.h"

namespace vpr {

class UserCameraAction: public IAction {

    public:
    UserCameraAction(SceneCamera* camera, UserInput* input);
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
};

}