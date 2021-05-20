#include "../../include/renderer/SceneRenderer.h"

namespace vpr {

SceneRenderer::SceneRenderer() {
    dirtyLightsData = true;
    time = 0.0;
    captureStencil = true;
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
        } else if(uniform == "time") {
            CHECK_GL_ERROR();

            glUniform1f(timeUniform.location, this->time);
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
        else if(uniform == "skybox_texture") {
            glUniform1i(SkyboxTextureUniform.location, textureMaskToPositions[SKYBOX_TEXTURE]);
            CHECK_GL_ERROR();
            }
        else if(uniform == "irradiance_texture") glUniform1i(IrradianceTextureUniform.location, textureMaskToPositions[IRRADIANCE_TEXTURE]);
        else if(uniform == "animated") glUniform1i(AnimationUniform.location, (int)material->getAnimated());
        else if(uniform == "num_frames") glUniform1ui(NumFramesUniform.location, material->getNumFrames());
        else if(uniform == "frame_length") glUniform1f(FrameLengthUniform.location, material->getFrameLength());
        else if(uniform == "frame_width") glUniform1f(FrameWidthUniform.location, material->getFrameWidth());
        else if(uniform == "view_pos") glUniform3f(ViewPositionUniform.location, camera->position.x,camera->position.y,camera->position.z);
        else if(uniform == "roughness") glUniform1f(RoughnessUniform.location, material->getRoughness());
        else if(uniform == "metalness") glUniform1f(MetalnessUniform.location, material->getMetalness());
        else if(uniform == "alpha") glUniform1f(AlphaUniform.location, material->getAlpha());
        else if(uniform == "fog") glUniform1i(FogUniform.location, (int)AppState::fog);

    }
}

void SceneRenderer::renderSkybox() {
    glDisable(GL_CULL_FACE);

    auto skyboxMesh = std::get<0>(skybox);
    auto skyboxMaterial = std::get<1>(skybox);
    auto skyboxData = std::get<2>(skybox);
    glDepthMask(GL_FALSE);
    CHECK_GL_ERROR();

    skyboxMesh->use();
    skyboxMaterial->use();
    applyModelUniforms(skyboxMesh, skyboxMaterial, skyboxData);
    CHECK_GL_ERROR();
    if(captureStencil) glStencilFunc(GL_ALWAYS,0b00000000, -1);
    glDrawElements(GL_TRIANGLES, skyboxMesh->numVertices,GL_UNSIGNED_INT,0);
    CHECK_GL_ERROR();

    glDepthMask(GL_TRUE);
    CHECK_GL_ERROR();
    glEnable(GL_CULL_FACE);
}

void SceneRenderer::renderModels() {

    if(captureStencil) {
        glClearStencil(0);
        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    } else {
        glDisable(GL_STENCIL_TEST);
    }

    if(std::get<0>(skybox) != nullptr) {
        renderSkybox();
    }


    std::vector<std::tuple<MeshAsset*, MaterialAsset*, ModelData*>> transparentModels;
    glEnable(GL_CULL_FACE);
    for(auto const& [mesh,value] : this->models) {
        mesh.second->use();
        for(auto const& [material, modelDataVector] : value) {
            material.second->use();
            if(material.second->hasAlpha()) {
                for(auto const& modelData : modelDataVector) {
                    if(!modelData->visible) continue;
                    transparentModels.push_back(std::make_tuple(mesh.second,material.second, modelData));
                }    
                continue;
            }
            for(auto const& modelData : modelDataVector) {
                if(!modelData->visible) {
                    std::cout << "skipping, model is hidden\n";
                    continue;
                }
                drawModel(mesh.second, material.second, modelData);
            }
        }
        glBindVertexArray(0);
    }

    sortByDistanceFromPoint(transparentModels, camera->position);

    glDisable(GL_CULL_FACE);
    for(auto& model : transparentModels) {
        auto mesh = std::get<0>(model);
        auto material = std::get<1>(model);
        auto modelData = std::get<2>(model);
        drawModel(mesh, material, modelData);
    }

    glStencilFunc(GL_NEVER,0, -1);
    glDisable(GL_STENCIL_TEST);

    time += 1.0;
    
    updateHoveredObject();
}

void SceneRenderer::drawModel(MeshAsset* mesh, MaterialAsset* material, ModelData* modelData) {
    if(captureStencil && modelData->selectable) {
        glStencilFunc(GL_ALWAYS,modelData->selectableId, -1);
        CHECK_GL_ERROR();

    }else {
        glStencilFunc(GL_ALWAYS,0b00000000, -1);
    }

    mesh->use();
    material->use();
    this->applyModelUniforms(mesh,material,modelData);
    glDrawElements(GL_TRIANGLES, mesh->numVertices,GL_UNSIGNED_INT,0);
}

void SceneRenderer::clearData() {
    models.clear();
    sunLights.clear();
    pointLights.clear();
    spotLights.clear();
    stencilIdToSceneObject.clear();
    nextStencilId = 1;
    
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
    nextStencilId = 1;
}

void SceneRenderer::addMesh(MeshAsset* mesh,MaterialAsset* material,ModelData* data) {
    models[MeshPair(mesh->getId(), mesh)][MaterialPair(material->getId(), material)].push_back(data);
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

void SceneRenderer::setSkybox(MeshAsset* mesh,MaterialAsset* material,ModelData* model) {
    this->skybox = std::make_tuple(mesh,material, model);
}

unsigned char SceneRenderer::getStencilBufferId(int x, int y) {
    unsigned char pixelId;
    glReadPixels(x,y,1,1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &pixelId);
    return pixelId;
}

unsigned int SceneRenderer::getStencilBufferObjectId(int x, int y) {
    unsigned char pixelId = getStencilBufferId(x,y);
    if(pixelId == 0) return 0;
    return stencilIdToSceneObject[pixelId];
}

unsigned char SceneRenderer::addSelectableItem(unsigned int  objectId) {
    stencilIdToSceneObject[nextStencilId] = objectId;
    return nextStencilId++;
}

void SceneRenderer::updateHoveredObject() {
    hoveredObject = getStencilBufferObjectId(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
}


}