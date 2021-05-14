#pragma once

#include <vector>
#include <tuple>

#include "../Types.h"

#include "../assets/MeshAsset.h"
#include "../assets/MaterialAsset.h"
#include "../gl/LightsUBO.h"

#include "../scene/ModelEntity.h"
#include "../scene/LightEntity.h"
#include "../scene/Scene.h"
#include "../scene/SceneCamera.h"

#include "SceneRenderingInstance.h"

namespace vpr {


struct ModelData;


class SceneRenderer : public SceneRenderingInstance {

    public:
    SceneRenderer();

    void render();

    void addMesh(MeshAsset*,MaterialAsset*,ModelData* data);

    void addSunLight(SunLightData*);
    void addPointLight(PointLightData*);
    void addSpotLight(SpotLightData*);

    void setCamera(CameraData* cameraData);

    void clearData();
    
    void beforeGather();
    void afterGather();
    
    void beforeDataUpdate();
    void afterDataUpdate();
    private:

    void renderModels();
    void applyModelUniforms(MeshAsset*, MaterialAsset*, ModelData*);

    void applyGenericUniforms();

    UniformData appliedUniformData;
    UniformData uniformData;

    MeshMaterialModelMap models;
    
    CameraData* camera;

    bool dirtyLightsData;
    std::vector<SunLightData*> sunLights;
    std::vector<PointLightData*> pointLights;
    std::vector<SpotLightData*> spotLights;

    LightsUBO lightsUBO;

};

}