#include "../../include/assets/TextureAsset.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../include/stb/stb_image.h"

#include <sstream>
#include <string>
#include <map>
#include <fstream>
#include <filesystem>

namespace vpr {

bool TextureAsset::loadConfiguration(string path) {
    std::ifstream file(path.c_str(), std::ios::in);
    if(!file) return false;

    nlohmann::json textureConfig;
    file >> textureConfig;

    TextureConfiguration& configuration = this->configuration;

    configuration.kind = textureConfig["kind"].get<string>();
    configuration.texture = textureConfig["texture"].get<string>();
    configuration.type = textureConfig["type"].get<string>();

    return true;
}

bool TextureAsset::load(string path) {
    loadConfiguration(path);

    if(configuration.kind == "2D") kind = GL_TEXTURE_2D;
    else if(configuration.kind == "3D") kind = GL_TEXTURE_3D;

    type = textureTypeToMask[configuration.type];

    int width,height, channels;
    fs::path texturePath = path;
    texturePath = texturePath.remove_filename();
    texturePath = texturePath.append(configuration.texture);
    std::cout << "Loading texture " << texturePath << std::endl;
    try {
        unsigned char* imageData = stbi_load(texturePath.string().c_str(),&width,&height,&channels, 0);

        glGenTextures(1,&handle);
        
        glTexParameteri(kind, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(kind, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);  

        glTexParameteri(kind, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(kind, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        
        glTexParameteri(kind, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(kind, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        
        if(kind == GL_TEXTURE_2D) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        }
        // glGenerateMipmap(kind);
        std::cout<<"loaded texture\n";
        return true;
    } catch(...) {
        std::cout << "Could not load texture asset: "<< path << std::endl;
        return false;
    }
}

void TextureAsset::use() {
    glActiveTexture(textureMaskToUnits[type]);
    glBindTexture(kind,handle);
}



}