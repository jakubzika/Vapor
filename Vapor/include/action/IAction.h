/**
 * \file       .h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Interface description for engine action.
 *  Engine action is registered, then every tick is triggered.
 *  Encapsultes small pieces of App/Game logic which handles all sorts of interaction and effects.
 *
*/

#pragma once

namespace vpr {

class IAction {
    public:
    virtual void tick(long msec) = 0;
    virtual bool isFinished() = 0;
};

}