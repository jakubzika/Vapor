#pragma once

#include <vector>

#include "pgr.h"

#include "../renderer/SceneRenderer.h"
#include "../renderer/SceneRenderingInstance.h"
#include "SceneObject.h"
#include "SceneEntity.h"
#include "SceneCamera.h"


namespace vpr {
    
class SceneRenderingInstance;
class SceneEntity;

class Scene {

    public:

    Scene();
    ~Scene();

    void gatherRenderingData(SceneRenderingInstance& renderer);
    void updateData(SceneRenderingInstance& renderer);

    void setRoot(SceneEntity* root);
    SceneEntity* getRoot();

    void setCamera(SceneCamera* camera);
    

    private:

    std::vector<SceneObject*> objects;
    
    SceneCamera* camera{nullptr};
    SceneEntity* root{nullptr};

    // camera

};

}