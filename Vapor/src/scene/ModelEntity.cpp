#include "../../include/scene/ModelEntity.h"

namespace vpr {

ModelEntity::ModelEntity() {

}

ModelEntity::ModelEntity(AssetTypeId mesh, AssetTypeId material) {
    this->meshId = mesh;
    this->materialId = material;
}

ModelEntity::ModelEntity(string meshName, string materialName) {
    this->meshId = MeshesHandler::get_instance()->getId(meshName);
    this->materialId = MaterialsHandler::get_instance()->getId(materialName);
}

void ModelEntity::generateRenderingData(SceneRenderingInstance& renderer) {
    if(this->meshId == 0 || this->materialId == 0) return;
    
    MeshesHandler* meshesHandler = MeshesHandler::get_instance();
    MaterialsHandler* materialsHandler = MaterialsHandler::get_instance();
    TexturesHandler* texturesHandler = TexturesHandler::get_instance();
    ShadersHandler* shadersHandler = ShadersHandler::get_instance();

    MeshAsset* mesh = meshesHandler->getAsset(this->meshId);
    MaterialAsset* material = materialsHandler->getAsset(this->materialId);

    this->data.availableTextures = material->getAvailableTextures();    
    
    renderer.addMesh(mesh,material,&this->data);
}

void ModelEntity::updatePositions(glm::mat4 model, glm::mat3 modelNormals) {
    model = glm::translate(model,this->position);
    model = glm::scale(model,this->scale);
    model = glm::rotate(model,this->rotation.x, glm::vec3(1.0,0.0,0.0));
    model = glm::rotate(model,this->rotation.y, glm::vec3(0.0,1.0,0.0));
    model = glm::rotate(model,this->rotation.z, glm::vec3(0.0,0.0,1.0));

    modelNormals = model;
    modelNormals = glm::transpose(glm::inverse(modelNormals));

    this->data.model = model;
    this->data.modelNormals = modelNormals;
}

}