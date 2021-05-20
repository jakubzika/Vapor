/**
 * \file       SceneObject.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Base scene "thing"
 *
*/

#pragma once

namespace vpr {

class SceneObject {
    public:
    SceneObject() {
        this->id = idGen++;
    }

    unsigned int getId() {return id;}
    static unsigned int idGen;

    private:

    protected:
    unsigned int id;

};


}