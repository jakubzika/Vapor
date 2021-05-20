/**
 * \file       Scene.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Contains all data about the current scene.
 *  In theory this is how levels could be deinfed.
 *
*/

#pragma once

#include <vector>
#include <map>

#include "pgr.h"

#include "../renderer/SceneRenderer.h"
#include "../renderer/SceneRenderingInstance.h"
#include "SceneObject.h"
#include "SceneEntity.h"
#include "SceneCamera.h"
#include "ModelEntity.h"


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
    void setSkybox(ModelEntity* skybox);

    unsigned short addSelectableItem(SceneObject*);
    

    private:


    std::vector<SceneObject*> objects;
    
    SceneCamera* camera{nullptr};
    SceneEntity* root{nullptr};

    ModelEntity* skybox{nullptr};
    
    // camera

};

}