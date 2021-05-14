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

    void use();
    

    private:

    GLuint handle;
    GLenum kind;
    TextureMask type;



    TextureConfiguration configuration;
};

}