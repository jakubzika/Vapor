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

    virtual void beforeGather();
    virtual void afterGather();
    virtual void beforeDataUpdate();
    virtual void afterDataUpdate();

    virtual void addMesh(MeshAsset* mesh, MaterialAsset* material, ModelData* data);
    virtual void setCamera(CameraData* cameraData);

    virtual void addSunLight(SunLightData*);
    virtual void addPointLight(PointLightData*);
    virtual void addSpotLight(SpotLightData*);

    // SceneRenderer* renderer;

};


}