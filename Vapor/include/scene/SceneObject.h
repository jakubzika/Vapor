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