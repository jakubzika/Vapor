#pragma once

#include "../Types.h"

#include "../assets/MaterialAsset.h"
#include "../assets/MeshAsset.h"

#include "../scene/SceneCamera.h"



namespace vpr {

struct ModelData;
struct SunLightData;
struct PointLightData;
struct SpotLightData;

class SceneRenderingInstance {

    public:

    virtual void beforeGather() = 0;
    virtual void afterGather() = 0;
    virtual void beforeDataUpdate() = 0;
    virtual void afterDataUpdate() = 0;

    virtual void addMesh(MeshAsset* mesh, MaterialAsset* material, ModelData* data) = 0;
    virtual void setSkybox(MeshAsset* mesh, MaterialAsset* material, ModelData* data) = 0;
    virtual void setCamera(CameraData* cameraData) = 0;

    virtual void addSunLight(SunLightData*) = 0;
    virtual void addPointLight(PointLightData*) = 0;
    virtual void addSpotLight(SpotLightData*) = 0;
    virtual unsigned char addSelectableItem(unsigned int) = 0;

    // SceneRenderer* renderer;

};


}