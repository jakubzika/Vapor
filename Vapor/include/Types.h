/**
 * \file       Types.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Contains all sorts of application constants, not only data.
 * Defines uniforms, attributes, UBO available in Vapor. And mapping between different representations of the information.
 * For json parsing
 *
*/

#pragma once

#include <map>
#include <utility> 
#include <filesystem>
#include <cstdint>

#include "pgr.h"

using std::string;

namespace vpr {

template<class AssetType> class AssetHandler;
class TextureAsset;
class MaterialAsset;

class MeshAsset;
class MaterialAsset;
class ShaderAsset;


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

static ShaderAttributeDescription positionAttribute{"position", GL_FLOAT,sizeof(GLfloat)*3,3,1};
static ShaderAttributeDescription normalAttribute{"normal", GL_FLOAT,sizeof(GLfloat)*3,3,2};
static ShaderAttributeDescription uvAttribute{"uv", GL_FLOAT,sizeof(GLfloat)*2,2,3};

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

static UniformAttributeDescription timeUniform{"time", GL_FLOAT,112, 1};
static UniformAttributeDescription AnimationUniform{"animated", GL_BOOL,2, 1};
static UniformAttributeDescription NumFramesUniform{"num_frames", GL_UNSIGNED_INT,3, 1};
static UniformAttributeDescription FrameLengthUniform{"frame_length", GL_FLOAT,4, 1};
static UniformAttributeDescription FrameWidthUniform{"frame_width", GL_FLOAT,5, 1};
static UniformAttributeDescription ViewPositionUniform{"view_pos", GL_FLOAT_VEC3,6, 4};

static UniformAttributeDescription ProjectionUniform{"projection", GL_FLOAT_MAT4,10, 20};
static UniformAttributeDescription ViewUniform{"view", GL_FLOAT_MAT4,30, 20};
static UniformAttributeDescription ModelUniform{"model", GL_FLOAT_MAT4,50, 20};
static UniformAttributeDescription PVMUniformInverse{"PVM_inverse", GL_FLOAT_MAT4,70, 20};
static UniformAttributeDescription AvailableTexturesUniform{"available_textures", GL_UNSIGNED_INT,90, 20};

static UniformAttributeDescription ColorTextureUniform{"color_texture", GL_INT,91, 1};
static UniformAttributeDescription NormalTextureUniform{"normal_texture", GL_INT,92, 1};
static UniformAttributeDescription SpecularTextureUniform{"specular_texture", GL_INT,93, 1};
static UniformAttributeDescription RoughnessTextureUniform{"roughness_texture", GL_INT,94, 1};
static UniformAttributeDescription MetalnessTextureUniform{"metalness_texture", GL_INT,95, 1};
static UniformAttributeDescription ReflectionTextureUniform{"reflection_texture", GL_INT,96, 1};
static UniformAttributeDescription SkyboxTextureUniform{"skybox_texture", GL_INT,97, 1};
static UniformAttributeDescription IrradianceTextureUniform{"irradiance_texture", GL_INT,98, 1};

static UniformAttributeDescription RoughnessUniform{"roughness", GL_FLOAT,110, 1};
static UniformAttributeDescription MetalnessUniform{"metalness", GL_FLOAT,111, 1};
static UniformAttributeDescription AlphaUniform{"alpha", GL_FLOAT,113, 1};
static UniformAttributeDescription FogUniform{"fog", GL_BOOL,114, 1};



struct UniformData {
    GLfloat time;
    glm::mat4 PVM;
    glm::mat3 PVM_inverse;  
};

// static UniformAttributeDescription timeUniform{"time", GL_FLOAT,0, 1};

static std::map<std::string, UniformAttributeDescription> fixedUniformLocations = {
    {timeUniform.name, timeUniform},
    {ProjectionUniform.name, ProjectionUniform},
    {ViewUniform.name, ViewUniform},
    {ModelUniform.name, ModelUniform},
    {PVMUniformInverse.name, PVMUniformInverse},
    {AvailableTexturesUniform.name, AvailableTexturesUniform},
    {ColorTextureUniform.name, ColorTextureUniform},
    {NormalTextureUniform.name, NormalTextureUniform},
    {SpecularTextureUniform.name, SpecularTextureUniform},
    {RoughnessTextureUniform.name, RoughnessTextureUniform},
    {MetalnessTextureUniform.name, MetalnessTextureUniform},
    {ReflectionTextureUniform.name, ReflectionTextureUniform},
    {SkyboxTextureUniform.name, SkyboxTextureUniform},
    {IrradianceTextureUniform.name, IrradianceTextureUniform},
    {AlphaUniform.name, AlphaUniform},
    {AnimationUniform.name, AnimationUniform},
    {NumFramesUniform.name, NumFramesUniform},
    {FrameLengthUniform.name, FrameLengthUniform},
    {FrameWidthUniform.name, FrameWidthUniform},
    {ViewPositionUniform.name, ViewPositionUniform},
    {RoughnessUniform.name, RoughnessUniform},
    {MetalnessUniform.name, MetalnessUniform},
    {AlphaUniform.name, AlphaUniform},
    {FogUniform.name, FogUniform}
};

typedef std::uint32_t TextureMask;

const TextureMask COLOR_TEXTURE     = 0b10000000;
const TextureMask NORMAL_TEXTURE    = 0b01000000;
const TextureMask SPECULAR_TEXTURE  = 0b00100000;
const TextureMask ROUGHNESS_TEXTURE = 0b00010000;
const TextureMask METALNESS_TEXTURE = 0b00001000;
const TextureMask REFLECTION_TEXTURE= 0b00000100;
const TextureMask SKYBOX_TEXTURE    = 0b00000010;
const TextureMask IRRADIANCE_TEXTURE= 0b00000001; 

static std::map<TextureMask, GLenum> textureMaskToUnits = {
    {COLOR_TEXTURE,       GL_TEXTURE0},
    {NORMAL_TEXTURE,      GL_TEXTURE1},
    {SPECULAR_TEXTURE,    GL_TEXTURE2},
    {ROUGHNESS_TEXTURE,   GL_TEXTURE3},
    {METALNESS_TEXTURE,   GL_TEXTURE4},
    {REFLECTION_TEXTURE,  GL_TEXTURE5},
    {SKYBOX_TEXTURE,      GL_TEXTURE6},
    {IRRADIANCE_TEXTURE,  GL_TEXTURE7},
};

static std::map<TextureMask, unsigned short> textureMaskToPositions = {
    {COLOR_TEXTURE,       0},
    {NORMAL_TEXTURE,      1},
    {SPECULAR_TEXTURE,    2},
    {ROUGHNESS_TEXTURE,   3},
    {METALNESS_TEXTURE,   4},
    {REFLECTION_TEXTURE,  5},
    {SKYBOX_TEXTURE,      6},
    {IRRADIANCE_TEXTURE,  7},
};

static std::map<string, TextureMask> textureTypeToMask = {
    {"COLOR",               COLOR_TEXTURE},
    {"NORMAL",              NORMAL_TEXTURE},
    {"SPECULAR",            SPECULAR_TEXTURE},
    {"ROUGHNESS",           ROUGHNESS_TEXTURE},
    {"METALNESS",           METALNESS_TEXTURE},
    {"REFLECTION",          REFLECTION_TEXTURE},
    {"SKYBOX",              SKYBOX_TEXTURE},
    {"IRRADIANCE",          IRRADIANCE_TEXTURE},
};

struct UniformBufferObjectDescription {
    string name;
    string shaderVariableName;
    GLuint location;
};

static UniformBufferObjectDescription LightsUniformBufferObject{"LIGHTS","lights", 0};

static std::map<string ,UniformBufferObjectDescription> fixedUniformBufferLocations = {
    {LightsUniformBufferObject.name, LightsUniformBufferObject}
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

namespace fs = std::filesystem;

typedef unsigned int AssetTypeId;
typedef AssetHandler<MeshAsset> MeshesHandler;
typedef AssetHandler<MaterialAsset> MaterialsHandler;
typedef AssetHandler<TextureAsset> TexturesHandler;
typedef AssetHandler<ShaderAsset> ShadersHandler;

struct ModelData;
struct MaterialData;

typedef std::pair<AssetTypeId, MeshAsset*> MeshPair;
typedef std::pair<AssetTypeId, MaterialAsset*> MaterialPair;

typedef std::vector<ModelData*> ModelVector;
typedef std::map<MaterialPair,ModelVector> MaterialModelMap;
typedef std::map<MeshPair,MaterialModelMap> MeshMaterialModelMap;

#define MAX_SUN_LIGHTS 2
#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 5

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

}

