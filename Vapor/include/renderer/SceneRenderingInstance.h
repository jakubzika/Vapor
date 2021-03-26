#pragma once

#include "../Types.h"

#include "../assets/MaterialAsset.h"
#include "../assets/MeshAsset.h"

#include "../scene/SceneCamera.h"



namespace vpr {

struct ModelData;
class SceneRenderingInstance {

    public:

    virtual void addMesh(MeshAsset* mesh, MaterialAsset* material, ModelData* data);
    virtual void setCamera(CameraData* cameraData);


    // SceneRenderer* renderer;

};


}