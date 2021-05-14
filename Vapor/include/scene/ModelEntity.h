#pragma once

#include "pgr.h"

#include "../renderer/SceneRenderingInstance.h"


#include "../Types.h"
#include "../assets/AssetHandler.h"
#include "../assets/MeshAsset.h"
#include "../assets/MaterialAsset.h"
#include "../assets/TextureAsset.h"
#include "../assets/ShaderAsset.h"

#include "SceneObject.h"
#include "SceneEntity.h"


namespace vpr {


struct ModelData {

    glm::mat4 model;
    glm::mat3 modelNormals;

    float roughness;
    float metalness;

    std::vector<std::tuple<TextureMask, TextureAsset*>> textures;

    ShaderAsset* shader;
    TextureMask availableTextures;
    

};



class SceneObject;
class SceneEntity;
class SceneRenderingInstance;

class ModelEntity : public SceneEntity {


    public: 
    ModelEntity();
    ModelEntity(AssetTypeId mesh, AssetTypeId material);
    ModelEntity(string meshName, string materialName);

    void generateRenderingData(SceneRenderingInstance& renderer);
    void updatePositions(glm::mat4 model, glm::mat3 modelNormals);


    private:

    ModelData data;

    AssetTypeId meshId;
    AssetTypeId materialId;
    
};

}