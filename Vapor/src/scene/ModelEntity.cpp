#include "../../include/scene/ModelEntity.h"

namespace vpr {

ModelEntity::ModelEntity() {

}

ModelEntity::ModelEntity(MeshAsset* mesh, MaterialAsset* material) {
    this->mesh = mesh;
    this->material = material;
}

void ModelEntity::generateRenderingData(SceneRenderingInstance& renderer) {
     if(this->mesh == nullptr || this->material == nullptr) return;

     renderer.addMesh(this->mesh,this->material,&this->data);
}

void ModelEntity::updatePositions(glm::mat4 model, glm::mat4 modelNormals) {
    model = glm::translate(model,this->position);
    model = glm::scale(model,this->scale);
    model = glm::rotate(model,this->rotation.x, glm::vec3(1.0,0.0,0.0));
    model = glm::rotate(model,this->rotation.y, glm::vec3(0.0,1.0,0.0));
    model = glm::rotate(model,this->rotation.z, glm::vec3(0.0,0.0,1.0));

    this->data.model = model;
    this->data.modelNormals = modelNormals;
}

}