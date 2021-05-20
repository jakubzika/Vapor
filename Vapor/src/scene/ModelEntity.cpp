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

std::tuple<MeshAsset*, MaterialAsset*, ModelData*> ModelEntity::getData() {
    MeshesHandler* meshesHandler = MeshesHandler::get_instance();
    MaterialsHandler* materialsHandler = MaterialsHandler::get_instance();
    TexturesHandler* texturesHandler = TexturesHandler::get_instance();
    ShadersHandler* shadersHandler = ShadersHandler::get_instance();

    MeshAsset* mesh = meshesHandler->getAsset(this->meshId);
    MaterialAsset* material = materialsHandler->getAsset(this->materialId);

    this->data.availableTextures = material->getAvailableTextures();
    this->data.selectable = selectable;
    this->data.entityId = this->id;
    this->data.position = this->position;

    return std::make_tuple(mesh, material, &this->data);
}

void ModelEntity::generateRenderingData(SceneRenderingInstance& renderer) {
    if(this->meshId == 0 || this->materialId == 0) return;
    
    auto renderingData = getData();
    renderer.addMesh(std::get<0>(renderingData), std::get<1>(renderingData), &this->data);

    if(selectable)  {
        this->data.selectableId = renderer.addSelectableItem(id);
        std::cout << "Stored id for item " << (unsigned short)this->data.selectableId << std::endl;
    }
}

void ModelEntity::updatePositions(glm::mat4 model, glm::mat3 modelNormals, bool hidden) {
    model = glm::scale(model,this->scale);
    model = glm::translate(model,this->position);
    model = glm::rotate(model,this->rotation.x, glm::vec3(1.0,0.0,0.0));
    model = glm::rotate(model,this->rotation.y, glm::vec3(0.0,1.0,0.0));
    model = glm::rotate(model,this->rotation.z, glm::vec3(0.0,0.0,1.0));

    modelNormals = model;
    modelNormals = glm::transpose(glm::inverse(modelNormals));

    if(!this->visible) std::cout << "not visible!\n";
    this->data.visible = this->visible && !hidden;
    this->data.model = model;
    this->data.modelNormals = modelNormals;
}

}