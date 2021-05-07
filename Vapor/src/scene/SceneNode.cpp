 #include "../../include/scene/SceneNode.h"

 namespace vpr {

SceneNode::SceneNode() {

}

void SceneNode::addChild(SceneEntity* child) {
    childs.push_back(child);
    child->setParent(this);
}

std::vector<SceneEntity*>* SceneNode::getChildren() {
    return &this->childs;
}

void SceneNode::generateRenderingData(SceneRenderingInstance& renderer) {
    for(auto& const child: this->childs) {
        child->generateRenderingData(renderer);
    }
}

void SceneNode::updatePositions(glm::mat4 model, glm::mat3 modelNormals) {

    model = glm::translate(model,this->position);
    model = glm::scale(model,this->scale);
    model = glm::rotate(model,this->rotation.x, glm::vec3(1.0,0.0,0.0));
    model = glm::rotate(model,this->rotation.y, glm::vec3(0.0,1.0,0.0));
    model = glm::rotate(model,this->rotation.z, glm::vec3(0.0,0.0,1.0));


    for(auto& const child : this->childs) 
    {
        child->updatePositions(model, modelNormals);
    }
}

}