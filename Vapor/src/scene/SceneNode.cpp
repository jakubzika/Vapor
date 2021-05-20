 #include "../../include/scene/SceneNode.h"


vpr::SceneNode::SceneNode() {

}

void vpr::SceneNode::addChild(vpr::SceneEntity* child) {
    childs.push_back(child);
    child->setParent(this);
}

std::vector<vpr::SceneEntity*>* vpr::SceneNode::getChildren() {
    return &this->childs;
}

void vpr::SceneNode::generateRenderingData(vpr::SceneRenderingInstance& renderer) {
    for(auto& const child: this->childs) {
        child->generateRenderingData(renderer);
    }
}

void vpr::SceneNode::updatePositions(glm::mat4 model, glm::mat3 modelNormals, bool hidden) {



    model = glm::scale(model,this->scale);
    model = glm::translate(model,this->position);
    model = glm::rotate(model,this->rotation.x, glm::vec3(1.0,0.0,0.0));
    model = glm::rotate(model,this->rotation.y, glm::vec3(0.0,1.0,0.0));
    model = glm::rotate(model,this->rotation.z, glm::vec3(0.0,0.0,1.0));


    for(auto& const child : this->childs) 
    {
        child->updatePositions(model, modelNormals, hidden || !visible);
    }
}
