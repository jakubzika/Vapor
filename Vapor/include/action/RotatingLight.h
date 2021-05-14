#pragma once

#include "pgr.h"

#include "IAction.h"
#include "../scene/SceneEntity.h"

namespace vpr {

class RotatingLight : public IAction {

    public:
    RotatingLight(SceneEntity* entity);
    void tick(long msec);
    bool isFinished() {return false;}

    private:

    glm::vec3 startingPosition;
    SceneEntity* entity;
    float time;

};

}