#pragma once
#include <iostream>
#include "SceneObject.h"
#include "../renderer/SceneRenderingInstance.h"

namespace vpr {


class SceneObject;
class SceneEntity : public SceneObject {
    public:
    SceneEntity();

    virtual void generateRenderingData(SceneRenderingInstance& renderer);
    virtual void updatePositions(glm::mat4 model, glm::mat3 modelNormals, bool hidden);

    void setParent(SceneEntity* parent);

    void setPosition(glm::vec3);
    void setRotation(glm::vec3);
    void setScale(glm::vec3);

    void setPosition(float x,float y,float z);
    void setRotation(float x,float y,float z);
    void setScale(float x,float y,float z);

    void hide() {
        this->visible = false;
        
        }
    void show() {this->visible = true;}
    bool isVisible() {return this->visible;}

    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale();
    
    private:
    SceneEntity* parent {nullptr};

    protected:
    glm::vec3 position{0.0,0.0,0.0};
    glm::vec3 rotation{0.0,0.0,0.0};
    glm::vec3 scale{1.0,1.0,1.0};

    bool visible;

};

}