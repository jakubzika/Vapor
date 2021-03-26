#pragma once

#include <map>
#include "pgr.h"
// #include "assets/AssetHandler.h"
// #include "assets/MeshAsset.h"


namespace vpr {

template<class AssetType> class AssetHandler;
class TextureAsset;
class MaterialAsset;

class MeshAsset;
class MaterialAsset;

class SceneObject;
class SceneEntity;
class SceneNode;
class ModelEntity;
class SceneRenderingInstance;
class Scene;
class SceneRenderer;

enum ModelType {
    SOLID = 0,
    TEXTURED,
    UNKNOWN
};

enum BufferType {
    ARRAY_BUFFER = GL_ARRAY_BUFFER,
    ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
};


#if !defined(ATTRIBUTE_LOCATIONS) 
#define ATTRIBUTE_LOCATIONS

struct ShaderAttributeDescription {
    std::string name;
    GLenum type;
    std::size_t size;
    GLuint count;
    GLuint location;
};

static ShaderAttributeDescription positionAttribute{"position", GL_FLOAT,sizeof(GLfloat)*3,3,0};
static ShaderAttributeDescription normalAttribute{"normal", GL_FLOAT,sizeof(GLfloat)*3,3,1};
static ShaderAttributeDescription uvAttribute{"uv", GL_FLOAT,sizeof(GLfloat)*2,2,2};

static std::map<std::string, ShaderAttributeDescription> fixedAttributeLocations {
    {positionAttribute.name, positionAttribute}, 
    {normalAttribute.name, normalAttribute}, 
    {uvAttribute.name, uvAttribute}
};

// static std::map<std::string, GLuint> fixedAttributeLocations = {{"position", 0}, {"normal", 1}, {"uv", 2}};
struct UniformAttributeDescription {
    std::string name;
    GLenum type;
    GLuint location;
    unsigned short locationsSize;
};

static UniformAttributeDescription timeUniform{"time", GL_FLOAT,0, 1};
static UniformAttributeDescription PVMUniform{"PVM", GL_FLOAT_MAT4,10, 20};

struct UniformData {
    GLfloat time;
    glm::mat4 PVM;

};
// static UniformAttributeDescription timeUniform{"time", GL_FLOAT,0, 1};

static std::map<std::string, UniformAttributeDescription> fixedUniformLocations = {
    {timeUniform.name, timeUniform},
    {PVMUniform.name, PVMUniform}
};

enum KeyEnum {
    Begin = -1,
    VPR_KEY_UNKNOWN,
    VPR_KEY_A,
    VPR_KEY_B,
    VPR_KEY_C,
    VPR_KEY_D,
    VPR_KEY_E,
    VPR_KEY_F,
    VPR_KEY_G,
    VPR_KEY_H,
    VPR_KEY_I,
    VPR_KEY_J,
    VPR_KEY_K,
    VPR_KEY_L,
    VPR_KEY_M,
    VPR_KEY_N,
    VPR_KEY_O,
    VPR_KEY_P,
    VPR_KEY_Q,
    VPR_KEY_R,
    VPR_KEY_S,
    VPR_KEY_T,
    VPR_KEY_U,
    VPR_KEY_V,
    VPR_KEY_W,
    VPR_KEY_X,
    VPR_KEY_Y,
    VPR_KEY_Z,
    VPR_KEY_SPACE,
    VPR_KEY_0,
    VPR_KEY_1,
    VPR_KEY_2,
    VPR_KEY_3,
    VPR_KEY_4,
    VPR_KEY_5,
    VPR_KEY_6,
    VPR_KEY_7,
    VPR_KEY_8,
    VPR_KEY_9,
    VPR_KEY_ESC,
    VPR_KEY_CTRL,
    VPR_KEY_SHIFT,
    VPR_KEY_ALT,
    VPR_KEY_ENTER,
    VPR_KEY_BACKSPACE,
    VPR_KEY_PLUS,
    VPR_KEY_MIN,
    VPR_KEY_UP,
    VPR_KEY_DOWN,
    VPR_KEY_LEFT,
    VPR_KEY_RIGHT,
    VPR_KEY_F1,
    VPR_KEY_F2,
    VPR_KEY_F3,
    VPR_KEY_F4,
    VPR_KEY_F5,
    VPR_KEY_F6,
    VPR_KEY_F7,
    VPR_KEY_F8,
    VPR_KEY_F9,
    VPR_KEY_F10,
    VPR_KEY_F11,
    VPR_KEY_F12,
    VPR_KEY_PAGE_UP,
    VPR_KEY_PAGE_DOWN,
    VPR_KEY_HOME,
    VPR_KEY_END,
    VPR_KEY_INSERT,
    SIZE,
};

// static std::map<std::string, GLuint> fixedUniformLocations = {{"time", 0}, {"PVM", 1}, {"other", 15}};

#endif

typedef unsigned int AssetTypeId;
typedef AssetHandler<MeshAsset> MeshesHandler;
typedef AssetHandler<MaterialAsset> MaterialsHandler;

struct ModelData;
typedef std::vector<ModelData*> ModelVector;
typedef std::map<MaterialAsset*,ModelVector> MaterialModelMap;
typedef std::map<MeshAsset*,MaterialModelMap> MeshMaterialModelMap;


}
