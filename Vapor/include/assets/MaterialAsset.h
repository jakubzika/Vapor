/**
 * \file       MaterialAsset.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Material asset containing information about materials, their configuration(alpha, animation, etc..) and textures it has
 *  
 *
*/

#pragma once

#include "pgr.h"
#include <vector>
#include <tuple>

#include "Asset.h"
#include "AssetHandler.h"
#include "../Types.h"
#include "TextureAsset.h"
#include "ShaderAsset.h"

namespace vpr {

using string = string;

struct MaterialConfiguration {
    string name;
    string shader;

    string colorTexture{""};
    string normalTexture{""};
    string specularTexture{""};
    string roughnessTexture{""};   
    string metalnessTexture{""};
    string reflectionTexture{""};
    string skyboxTexture{""};
    string irradianceTexture{""};

    ModelType type;
    float roughness{-1.0f};
    float metalness{-1.0f};

    float alpha{1.0};
    bool hasAlphaTexture{false};

    bool animated{false};
    unsigned int numFrames;
    float frameLength;
    float frameWidth;
};

// struct MaterialData {
//     TextureMask availableTextures;
//     std::vector<std::tuple<TextureMask, TextureAsset*>> textures;

//     ShaderAsset* shader;
// };



class MaterialAsset : public Asset {

    public:
    

    bool load(string path) override;
    bool loadConfiguration(string path);
    void use();

    MaterialConfiguration getMaterialConfiguration() {return configuration;};
    AssetTypeId getShaderId() {return shader;};

    TextureMask getAvailableTextures();
    std::vector<std::tuple<TextureMask, AssetTypeId>> getTextureIds();
    ShaderAsset* getShaderAsset();

    std::vector<std::tuple<TextureMask, TextureAsset*>> getTextureAssets();


    float getAlpha() {return alpha;}

    bool hasAlpha() { return alpha != 1.0 || alphaTexture;}

    bool getAnimated() {
        return animated;}
    unsigned int getNumFrames() {return animated ? numFrames : 0;}
    float getFrameLength() {return animated ? frameLength : 0;}
    float getFrameWidth() {return animated ? frameWidth : 0;}

    float getMetalness() {return metalness;}
    float getRoughness() {return roughness;}

    private:

    ModelType modelType;

    AssetTypeId colorTexture{0};
    AssetTypeId normalTexture{0};
    AssetTypeId specularTexture{0};
    AssetTypeId roughnessTexture{0};
    AssetTypeId metalnessTexture{0};
    AssetTypeId reflectionTexture{0};
    AssetTypeId skyboxTexture{0};
    AssetTypeId irradianceTexture{0};

    AssetTypeId shader;

    float alpha;
    bool alphaTexture;

    bool animated{false};
    unsigned int numFrames;
    float frameLength;
    float frameWidth;

    float metalness;
    float roughness;

    MaterialConfiguration configuration;



};

}