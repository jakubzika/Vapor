/**
 * \file       SelectableItems.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      Action for handling filling of the pool
 *
 *  Small state machine implementation which handles interaction with valve.
 *  Clicking the valve causes the pool to fill and water filling streams to show up. Again clicking it empties the pool.
 *
*/

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