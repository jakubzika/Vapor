#include "../../include/renderer/SceneRenderingInstance.h"

namespace vpr {
    

void SceneRenderingInstance::beforeGather() {}
void SceneRenderingInstance::afterGather() {}
void SceneRenderingInstance::beforeDataUpdate() {}
void SceneRenderingInstance::afterDataUpdate() {}

void SceneRenderingInstance::addMesh(MeshAsset* mesh, MaterialAsset* material, ModelData* data) {}
void SceneRenderingInstance::setCamera(CameraData* cameraData) {}

void SceneRenderingInstance::addSunLight(SunLightData*) {}
void SceneRenderingInstance::addPointLight(PointLightData*) {}
void SceneRenderingInstance::addSpotLight(SpotLightData*) {}

}