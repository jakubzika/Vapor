#include "../../include/renderer/SceneRenderer.h"

namespace vpr {

SceneRenderer::SceneRenderer() {

}

void SceneRenderer::addMesh(MeshAsset* mesh,MaterialAsset* material,ModelData* data) {
    models[mesh][material].push_back(data);
}

void SceneRenderer::setCamera(CameraData* camera) {
    this->camera = camera;
}

void SceneRenderer::render() {
    applyGenericUniforms();
    renderModels();
}

void SceneRenderer::applyGenericUniforms() {
    uniformData.time = 0.0;

}

void SceneRenderer::applyModelUniforms(MeshAsset* mesh, MaterialAsset* material, ModelData* modelData) {
    std::vector<std::string> materialUniforms = material->getMaterialConfiguration().uniforms;

    for(auto uniform: materialUniforms) {
        if(uniform == "PVM") {
            glm::mat4 PVM = this->camera->projection * this->camera->view * modelData->model;
            // glm::vec4 tester = PVM * glm::vec4(10.0,0.0,4.0,1.0);
                CHECK_GL_ERROR();

            glUniformMatrix4fv(PVMUniform.location,1,GL_FALSE,&PVM[0][0]);
                CHECK_GL_ERROR();

        } else if(uniform == "time" && this->appliedUniformData.time != this->uniformData.time) {
                CHECK_GL_ERROR();

            glUniform1f(timeUniform.location, this->uniformData.time);
                CHECK_GL_ERROR();

            this->appliedUniformData.time = this->uniformData.time;
        }
        
    }
}


void SceneRenderer::renderModels() {

    

    for(auto const& [mesh,value] : this->models) {
        mesh->use();
        for(auto const& [material, modelDataVector] : value) {
            material->use();
            for(auto const& modelData : modelDataVector) {
                this->applyModelUniforms(mesh,material,modelData);
                glDrawElements(GL_TRIANGLES, mesh->numVertices,GL_UNSIGNED_INT,0);
                CHECK_GL_ERROR();

            }
            
        }
        glBindVertexArray(0);
    }
    {
        
    }
}



}