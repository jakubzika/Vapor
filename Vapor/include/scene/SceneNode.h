#pragma once

#include <vector>

#include "SceneObject.h"
#include "SceneEntity.h"
#include "../renderer/SceneRenderingInstance.h"

namespace vpr {

class SceneNode : public SceneEntity {

    public:

    SceneNode();

    void addChild(SceneEntity* child);
    std::vector<SceneEntity*>* getChildren();

    void generateRenderingData(SceneRenderingInstance& renderer);
    void updatePositions(glm::mat4 model, glm::mat3 modelNormals, bool hidden);

    private:

    std::vector<SceneEntity*> childs;

};

}
