/**
 * \file       TextureAsset.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Texture asset
 *
*/

#pragma once
#include "Asset.h"

#include "pgr.h"

namespace vpr {

struct TextureConfiguration {
    string kind;
    string texture;
    string type;
};

class TextureAsset: public Asset {

    public:
    bool loadConfiguration(string path);
    bool load(string path);

    bool load2DTexture(fs::path texturePath);
    bool loadCubemapTexture(fs::path path[6]);

    void use();
    

    private:

    GLuint handle;
    GLenum kind;
    TextureMask type;

    TextureConfiguration configuration;
};

}