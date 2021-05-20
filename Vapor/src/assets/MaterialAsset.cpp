#include "../../include/assets/MaterialAsset.h"

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <fstream>
#include <filesystem>

#include "../../include/nlohmann/json.hpp"
#include "../../include/Util.h"

namespace vpr {


bool MaterialAsset::loadConfiguration(std::string path) {

    std::ifstream file(path.c_str(), std::ios::in);
    if(!file) return false;

    nlohmann::json materialConfig;
    file >> materialConfig;

    MaterialConfiguration& configuration = this->configuration;

    configuration.roughness = materialConfig["roughness"].get<float>();
    configuration.metalness = materialConfig["metalness"].get<float>();
    configuration.shader = materialConfig["shader"].get<string>();

    if(materialConfig["textures"].is_object()) {
        auto textures = materialConfig["textures"];
        if(textures["color"].is_string()) configuration.colorTexture = textures["color"].get<string>();
        if(textures["normal"].is_string()) configuration.normalTexture = textures["normal"].get<string>();
        if(textures["specular"].is_string()) configuration.specularTexture = textures["specular"].get<string>();
        if(textures["roughness"].is_string()) configuration.roughnessTexture = textures["roughness"].get<string>();
        if(textures["metalness"].is_string()) configuration.metalnessTexture = textures["metalness"].get<string>();
        if(textures["reflection"].is_string()) configuration.reflectionTexture = textures["reflection"].get<string>();
        if(textures["skybox"].is_string()) configuration.skyboxTexture = textures["skybox"].get<string>();
        if(textures["irradiance"].is_string()) configuration.irradianceTexture = textures["irradiance"].get<string>();
    }

    if(materialConfig["alpha"].is_number_float()) {
        configuration.alpha = materialConfig["alpha"].get<float>();
    }

    if(materialConfig["alpha-texture"].is_boolean()) {
        configuration.hasAlphaTexture = materialConfig["alpha-texture"].get<bool>();
    }

    if(materialConfig["animated"].is_boolean() && materialConfig["animated"].get<bool>()) {
        configuration.animated = true;

        configuration.numFrames = materialConfig["num-frames"].get<int>();
        configuration.frameLength = materialConfig["frame-length"].get<float>();
        configuration.frameWidth = materialConfig["frame-width"].get<float>();
    }

    file.close();

    return true;
}

bool MaterialAsset::load(std::string configurationPath) {
    
    this->loadConfiguration(configurationPath);

    TexturesHandler* texturesHandler = TexturesHandler::get_instance();

    if(!configuration.colorTexture.empty()) colorTexture = texturesHandler->getId(configuration.colorTexture);
    if(!configuration.normalTexture.empty()) normalTexture = texturesHandler->getId(configuration.normalTexture);
    if(!configuration.specularTexture.empty()) specularTexture = texturesHandler->getId(configuration.specularTexture);
    if(!configuration.roughnessTexture.empty()) roughnessTexture = texturesHandler->getId(configuration.roughnessTexture);
    if(!configuration.metalnessTexture.empty()) metalnessTexture = texturesHandler->getId(configuration.metalnessTexture);
    if(!configuration.reflectionTexture.empty()) reflectionTexture = texturesHandler->getId(configuration.reflectionTexture);
    if(!configuration.skyboxTexture.empty()) skyboxTexture = texturesHandler->getId(configuration.skyboxTexture);
    if(!configuration.irradianceTexture.empty()) irradianceTexture = texturesHandler->getId(configuration.irradianceTexture);

    alpha = configuration.alpha;
    alphaTexture =configuration.hasAlphaTexture;

    animated = configuration.animated;
    if(animated) {
        numFrames = configuration.numFrames;
        frameLength = configuration.frameLength;
        frameWidth = configuration.frameWidth;
    }

    roughness = configuration.roughness;
    metalness = configuration.metalness;
    ShadersHandler* shadersHandler = ShadersHandler::get_instance();
    
    shader = shadersHandler->getId(configuration.shader);

    return true;
}

TextureMask MaterialAsset::getAvailableTextures() {
    TextureMask available = 0;
    if(colorTexture) available |= COLOR_TEXTURE;
    if(normalTexture) available |= NORMAL_TEXTURE;
    if(specularTexture) available |= SPECULAR_TEXTURE;
    if(roughnessTexture) available |= ROUGHNESS_TEXTURE;
    if(metalnessTexture) available |= METALNESS_TEXTURE;
    if(reflectionTexture) available |= REFLECTION_TEXTURE;
    if(skyboxTexture) available |= SKYBOX_TEXTURE;
    if(irradianceTexture) available |= IRRADIANCE_TEXTURE;
    return available;
}

std::vector<std::tuple<TextureMask, AssetTypeId>> MaterialAsset::getTextureIds() {
    std::vector<std::tuple<TextureMask, AssetTypeId>> ids;
    if(colorTexture) ids.push_back(std::make_tuple(COLOR_TEXTURE,colorTexture));
    if(normalTexture) ids.push_back(std::make_tuple(NORMAL_TEXTURE,normalTexture));
    if(specularTexture) ids.push_back(std::make_tuple(SPECULAR_TEXTURE,specularTexture));
    if(roughnessTexture) ids.push_back(std::make_tuple(ROUGHNESS_TEXTURE,roughnessTexture));
    if(metalnessTexture) ids.push_back(std::make_tuple(METALNESS_TEXTURE,metalnessTexture));
    if(reflectionTexture) ids.push_back(std::make_tuple(REFLECTION_TEXTURE,reflectionTexture));
    if(skyboxTexture) ids.push_back(std::make_tuple(SKYBOX_TEXTURE,skyboxTexture));
    if(irradianceTexture) ids.push_back(std::make_tuple(IRRADIANCE_TEXTURE,irradianceTexture));

    return ids;
}

std::vector<std::tuple<TextureMask, TextureAsset*>> MaterialAsset::getTextureAssets() {
    TexturesHandler* texturesHandler = TexturesHandler::get_instance();
    
    std::vector<std::tuple<TextureMask, TextureAsset*>> assets;

    if(colorTexture) assets.push_back(std::make_tuple(COLOR_TEXTURE,texturesHandler->getAsset(colorTexture)));
    if(normalTexture) assets.push_back(std::make_tuple(NORMAL_TEXTURE,texturesHandler->getAsset(normalTexture)));
    if(specularTexture) assets.push_back(std::make_tuple(SPECULAR_TEXTURE,texturesHandler->getAsset(specularTexture)));
    if(roughnessTexture) assets.push_back(std::make_tuple(ROUGHNESS_TEXTURE,texturesHandler->getAsset(roughnessTexture)));
    if(metalnessTexture) assets.push_back(std::make_tuple(METALNESS_TEXTURE,texturesHandler->getAsset(metalnessTexture)));
    if(reflectionTexture) assets.push_back(std::make_tuple(REFLECTION_TEXTURE,texturesHandler->getAsset(reflectionTexture)));
    if(skyboxTexture) assets.push_back(std::make_tuple(SKYBOX_TEXTURE,texturesHandler->getAsset(skyboxTexture)));
    if(irradianceTexture) assets.push_back(std::make_tuple(IRRADIANCE_TEXTURE,texturesHandler->getAsset(irradianceTexture)));
    return assets;
}

ShaderAsset* MaterialAsset::getShaderAsset() {
    return ShadersHandler::get_instance()->getAsset(shader);
}

void MaterialAsset::use() {
    getShaderAsset()->use();

    auto textures = getTextureAssets();
    for(auto texture: textures) {
        std::get<1>(texture)->use();
    }

}


}