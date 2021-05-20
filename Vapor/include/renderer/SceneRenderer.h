#pragma once

#include <vector>
#include <tuple>

#include "../Types.h"
#include "../Util.h"

#include "../engine/State.h"

#include "../assets/MeshAsset.h"
#include "../assets/MaterialAsset.h"
#include "../gl/LightsUBO.h"

#include "../scene/ModelEntity.h"
#include "../scene/LightEntity.h"
#include "../scene/Scene.h"
#include "../scene/SceneCamera.h"
#include "../scene/SceneObject.h"

#include "SceneRenderingInstance.h"

namespace vpr {


struct ModelData;


class SceneRenderer : public SceneRenderingInstance {

    public:
    SceneRenderer();

    void render();

    void addMesh(MeshAsset*,MaterialAsset*,ModelData* data);
    void setSkybox(MeshAsset*,MaterialAsset*,ModelData* data);

    void addSunLight(SunLightData*);
    void addPointLight(PointLightData*);
    void addSpotLight(SpotLightData*);
    unsigned char addSelectableItem(unsigned int objectId);


    void setCamera(CameraData* cameraData);

    void clearData();
    
    void beforeGather();
    void afterGather();
    
    void beforeDataUpdate();
    void afterDataUpdate();
    
    unsigned char getStencilBufferId(int x, int y);
    unsigned int getStencilBufferObjectId(int x, int y);
    unsigned int getHoveredObject() {return hoveredObject;}


    private:

    void renderModels();
    void renderSkybox();


    void applyModelUniforms(MeshAsset*, MaterialAsset*, ModelData*);
    void drawModel(MeshAsset*, MaterialAsset*, ModelData*);

    void applyGenericUniforms();



    float time;
    UniformData appliedUniformData;
    UniformData uniformData;

    MeshMaterialModelMap models;
    
    CameraData* camera;

    bool dirtyLightsData;
    std::vector<SunLightData*> sunLights;
    std::vector<PointLightData*> pointLights;
    std::vector<SpotLightData*> spotLights;
    
    std::tuple<MeshAsset*,MaterialAsset*,ModelData*> skybox;

    LightsUBO lightsUBO;

    bool captureStencil;

    void updateHoveredObject();
    unsigned int hoveredObject{0};
    unsigned char nextStencilId;
    std::map<unsigned char, unsigned int> stencilIdToSceneObject;
};

}