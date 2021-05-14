#include "../../include/renderer/SceneRenderer.h"

namespace vpr {

SceneRenderer::SceneRenderer() {
    dirtyLightsData = true;
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
    std::vector<std::string> materialUniforms = material->getShaderAsset()->getConfiguration()->uniforms;

    // for(auto uniform : materialUniforms) {
    //     std::cout << "uniform location for "<< uniform << " is " <<glGetUniformLocation(material->getShaderAsset()->getProgram(), uniform.c_str()) << std::endl;
    // }

    for(auto uniform: materialUniforms) {
        if(uniform == "projection") {
            glUniformMatrix4fv(ProjectionUniform.location,1,GL_FALSE,&this->camera->projection[0][0]);
            CHECK_GL_ERROR();

        } else if(uniform == "view") {
            glUniformMatrix4fv(ViewUniform.location,1,GL_FALSE,&this->camera->view[0][0]);
            CHECK_GL_ERROR();
        } else if(uniform == "model") {
            glUniformMatrix4fv(ModelUniform.location,1,GL_FALSE,&modelData->model[0][0]);
            CHECK_GL_ERROR();

        } else if(uniform == "PVM_inverse") {
            glUniformMatrix3fv(PVMUniformInverse.location,1,GL_FALSE,&modelData->modelNormals[0][0]);
            CHECK_GL_ERROR();
        } else if(uniform == "time" && this->appliedUniformData.time != this->uniformData.time) {
            CHECK_GL_ERROR();

            glUniform1f(timeUniform.location, this->uniformData.time);
                CHECK_GL_ERROR();

            this->appliedUniformData.time = this->uniformData.time;
        }  else if(uniform == "available_textures") {
            glUniform1ui(AvailableTexturesUniform.location, modelData->availableTextures);
            CHECK_GL_ERROR();

        }
        else if(uniform == "color_texture") {
            CHECK_GL_ERROR();
            glUniform1i(ColorTextureUniform.location, textureMaskToPositions[COLOR_TEXTURE]);
            CHECK_GL_ERROR();

        }
        else if(uniform == "normal_texture") glUniform1i(NormalTextureUniform.location, textureMaskToPositions[NORMAL_TEXTURE]);
        else if(uniform == "specular_texture") glUniform1i(SpecularTextureUniform.location, textureMaskToPositions[SPECULAR_TEXTURE]);
        else if(uniform == "roughness_texture") glUniform1i(RoughnessTextureUniform.location, textureMaskToPositions[ROUGHNESS_TEXTURE]);
        else if(uniform == "metalness_texture") glUniform1i(MetalnessTextureUniform.location, textureMaskToPositions[METALNESS_TEXTURE]);
        else if(uniform == "reflection_texture") glUniform1i(ReflectionTextureUniform.location, textureMaskToPositions[REFLECTION_TEXTURE]);
        
    }
}


void SceneRenderer::renderModels() {

    

    for(auto const& [mesh,value] : this->models) {
        mesh->use();
        for(auto const& [material, modelDataVector] : value) {
            material->use();
            for(auto const& modelData : modelDataVector) {
                this->applyModelUniforms(mesh,material,modelData);
                CHECK_GL_ERROR();
                glDrawElements(GL_TRIANGLES, mesh->numVertices,GL_UNSIGNED_INT,0);
                CHECK_GL_ERROR();
            }
            
        }
        glBindVertexArray(0);
    }
    {
        
    }
}

void SceneRenderer::clearData() {
    models.clear();
    sunLights.clear();
    pointLights.clear();
    spotLights.clear();
}

void SceneRenderer::beforeDataUpdate() {

}

void SceneRenderer::afterDataUpdate() {
    if(dirtyLightsData || true) {
        lightsUBO.uploadData(sunLights, pointLights, spotLights);
        dirtyLightsData = false;
    }
}

void SceneRenderer::afterGather() {
}

void SceneRenderer::beforeGather() {
    clearData();
}

void SceneRenderer::addMesh(MeshAsset* mesh,MaterialAsset* material,ModelData* data) {
    models[mesh][material].push_back(data);
}

void SceneRenderer::addSunLight(SunLightData* data) {
    std::cout<<"enderer adding sunlight\n";
    dirtyLightsData = true;
    if(sunLights.size() < MAX_SUN_LIGHTS)
        sunLights.push_back(data);
    else std::cout << "Maximum amount of sun lights reached. Ignoring\n";
}

void SceneRenderer::addPointLight(PointLightData* data) {
    dirtyLightsData = true;
    if(pointLights.size() < MAX_POINT_LIGHTS)
        pointLights.push_back(data);
    else std::cout << "Maximum amount of point lights reached. Ignoring\n";
}
void SceneRenderer::addSpotLight(SpotLightData* data) {
    dirtyLightsData = true;
    if(spotLights.size() < MAX_SPOT_LIGHTS)
        spotLights.push_back(data);
    else std::cout << "Maximum amount of point lights reached. Ignoring\n";
}


}