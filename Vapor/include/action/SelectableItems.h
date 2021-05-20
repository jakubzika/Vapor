#pragma once

#include "pgr.h"

#include <iostream>
#include <vector>

#include "IAction.h"
#include "../scene/SceneEntity.h"
#include "../renderer/SceneRenderer.h"
#include "../scene/ModelEntity.h"
#include "../input/UserInput.h"
#include "./EntityHovering.h"

enum States {
    STATE_EMPTY, STATE_FILLING_WATER, STATE_FILLED_WATER, STATE_EMPTYING_WATER
};

enum Action {
    ACTION_CLICKED, ACTION_TIME_TICK
};

namespace vpr {

class SelectableItems : public IAction {

    public:
    SelectableItems(UserInput* input,SceneRenderer* renderer, ModelEntity* activator, std::vector<SceneEntity*> toHide, SceneEntity* waterLevel);
    void tick(long msec);
    bool isFinished() {return false;}

    void updateWaterPosition();

    private:

    UserInput* input;

    ModelEntity* activator;
    std::vector<SceneEntity*> toHide;
    SceneEntity* waterLevel;

    SceneRenderer* renderer;

    glm::vec3 activatorRotation;

    float time;
    int width,height;

    bool setState(States state, int stateTimeout);
    States state;
    int timeInState;
    int stateTimeoutBlock{0};

};

}