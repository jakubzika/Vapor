#pragma once

#include "pgr.h"

#include "../renderer/SceneRenderingInstance.h"



#include "../assets/MeshAsset.h"
#include "../assets/MaterialAsset.h"

#include "SceneObject.h"
#include "SceneEntity.h"


namespace vpr {


struct ModelData {

    glm::mat4 model;
    glm::mat3 modelNormals;

    float roughness;
    float metalness;

    AssetTypeId colorTexture;
    AssetTypeId normalTexture;
    AssetTypeId specularTexture;
    AssetTypeId roughnessTexture;
    AssetTypeId metalnessTexture;

};

class SceneObject;
class SceneEntity;
class SceneRenderingInstance;

class ModelEntity : public SceneEntity {


    public: 
    ModelEntity();
    ModelEntity(MeshAsset* mesh, MaterialAsset* material);

    void generateRenderingData(SceneRenderingInstance& renderer);
    void updatePositions(glm::mat4 model, glm::mat3 modelNormals);


    private:

    ModelData data;
    MeshAsset* mesh;
    MaterialAsset* material;
    
};

}