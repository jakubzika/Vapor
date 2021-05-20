#pragma once

#include "pgr.h"

#include "IAction.h"
#include "../input/UserInput.h"
#include "../engine/State.h"

namespace vpr {

class UserKeyAction : public IAction {

    public:
    UserKeyAction(UserInput* input);
    void tick(long msec);
    bool isFinished() {return false;}

    private:
    UserInput* input;
};

}