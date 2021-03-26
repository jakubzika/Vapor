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
