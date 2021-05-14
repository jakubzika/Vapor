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

    ModelType type;
    float roughness{-1.0f};
    float metalness{-1.0f};
        
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


    private:

    ModelType modelType;

    AssetTypeId colorTexture{0};
    AssetTypeId normalTexture{0};
    AssetTypeId specularTexture{0};
    AssetTypeId roughnessTexture{0};
    AssetTypeId metalnessTexture{0};
    AssetTypeId reflectionTexture{0};

    AssetTypeId shader;

    MaterialConfiguration configuration;



};

}