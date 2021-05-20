/**
 * \file       SceneRenderer.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Handles rendering scene data.
 *  Models do not render themselves. They pass their data from Scene graph traversal to the renderer.
 *  And renderer can sort the models accordingly for best performance.
 *
*/

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


    /**
     * @brief Starts the render pass
     * 
     */
    void render();


    /**
     * @brief Registers new model to be rendered
     * 
     * @param mesh 
     * @param material 
     * @param data 
     */
    void addMesh(MeshAsset* mesh,MaterialAsset* material,ModelData* data);


    /**
     * @brief Set the Skybox object
     * 
     * @param mesh 
     * @param material 
     * @param data 
     */
    void setSkybox(MeshAsset* mesh,MaterialAsset* material,ModelData* data);


    /**
     * @brief Registers new sun light
     * 
     * @param light 
     */
    void addSunLight(SunLightData* light);


    /**
     * @brief Registers new point light
     * 
     * @param light 
     */
    void addPointLight(PointLightData* light);


    /**
     * @brief Registers new spot light
     * 
     * @param light 
     */
    void addSpotLight(SpotLightData* light);


    /**
     * @brief Registers item which makes it render specific id for it into the stencil buffer
     * 
     * @param objectId 
     * @return unsigned char id in stencil buffer corresponding to the specified object
     */
    unsigned char addSelectableItem(unsigned int objectId);


    /**
     * @brief Set the Camera object
     * 
     * @param cameraData 
     */
    void setCamera(CameraData* cameraData);


    /**
     * @brief Clears all the rendering data
     * 
     */
    void clearData();


    /**
     * @brief Is called before rendering data gather
     * 
     */
    void beforeGather();


    /**
     * @brief Is called after rendering data gather
     * 
     */
    void afterGather();
    

    /**
     * @brief Is called before rendering data update
     * 
     */
    void beforeDataUpdate();


    /**
     * @brief Is called after rendering data update
     * 
     */
    void afterDataUpdate();
    

    /**
     * @brief Retrieves value from stencil buffer
     * 
     * @param x 
     * @param y 
     * @return unsigned char 
     */
    unsigned char getStencilBufferId(int x, int y);


    /**
     * @brief Retrieves value from stencil buffer and maps the stencil value into object id
     * 
     * @param x 
     * @param y 
     * @return unsigned int 
     */
    unsigned int getStencilBufferObjectId(int x, int y);


    /**
     * @brief Retrieves object id from stencil buffer from center of the screen.
     * 
     * @return unsigned int 
     */
    unsigned int getHoveredObject() {return hoveredObject;}


    private:

    void renderModels();
    void renderSkybox();


    void applyModelUniforms(MeshAsset*, MaterialAsset*, ModelData*);
    void drawModel(MeshAsset*, MaterialAsset*, ModelData*);

    /**
     * @brief Not in use
     * 
     */
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