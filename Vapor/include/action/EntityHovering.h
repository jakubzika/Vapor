#pragma once

#include "pgr.h"

#include "IAction.h"
#include "../scene/SceneEntity.h"

namespace vpr {

class EntityHovering : public IAction {

    public:
    EntityHovering(SceneEntity* entity);
    void tick(long msec);
    bool isFinished() {return false;}

    private:

    glm::vec3 startingPosition;
    SceneEntity* entity;
    float time;

};

}