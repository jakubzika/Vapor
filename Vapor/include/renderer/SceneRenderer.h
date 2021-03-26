#pragma once

#include <vector>
#include <tuple>

#include "../Types.h"

#include "../assets/MeshAsset.h"
#include "../assets/MaterialAsset.h"

#include "../scene/ModelEntity.h"
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
    void setCamera(CameraData* cameraData);
    private:

    void renderModels();
    void applyModelUniforms(MeshAsset*, MaterialAsset*, ModelData*);

    void applyGenericUniforms();

    UniformData appliedUniformData;
    UniformData uniformData;

    MeshMaterialModelMap models;
    CameraData* camera;

};

}