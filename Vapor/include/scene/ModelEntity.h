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
    glm::mat4 modelNormals;
};

class SceneObject;
class SceneEntity;
class SceneRenderingInstance;

class ModelEntity : public SceneEntity {


    public: 
    ModelEntity();
    ModelEntity(MeshAsset* mesh, MaterialAsset* material);

    void generateRenderingData(SceneRenderingInstance& renderer);
    void updatePositions(glm::mat4 model, glm::mat4 modelNormals);


    private:

    ModelData data;
    // hehe, instanced std::vector<data>
    MeshAsset* mesh;
    MaterialAsset* material;

};

}