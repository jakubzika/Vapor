#pragma once

namespace vpr {

class IAction {
    public:
    virtual void tick(long msec) = 0;
    virtual bool isFinished() = 0;
};

}