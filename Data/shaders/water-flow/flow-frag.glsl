#version 330
#extension GL_ARB_explicit_uniform_location : require
#extension GL_EXT_gpu_shader4 : enable

out vec4 fragmentColor;

in vec3 position_f;
in vec3 normal_f;
in vec2 uv_f;

layout(location = 112)uniform float time;
layout(location = 113)uniform float alpha;
layout(location =6)uniform vec3 view_pos;


layout(location = 90)uniform uint available_textures;
layout(location = 91)uniform sampler2D color_texture;
layout(location = 92)uniform sampler2D normal_texture;
layout(location = 93)uniform sampler2D specular_texture;
layout(location = 94)uniform sampler2D roughness_texture;
layout(location = 95)uniform sampler2D metalness_texture;
layout(location = 96)uniform sampler2D reflection_texture;
layout(location = 97)uniform sampler2D skybox_texture;
layout(location = 98)uniform sampler2D irradiance_texture;

layout(location = 114)uniform bool fog;


#define MAX_SUN_LIGHTS 2
#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 5

struct SunLight {
    vec4 color;
    vec4 angle;
    float strength;
};

struct PointLight {
    vec4 position;
    vec4 color;
    vec4 attentuation;
    float strength;    
};

struct SpotLight {
    vec4 color;
    vec4 position;
    vec4 angle;
    vec4 cone;
    float strength;
};

layout (std140) uniform lights {
    SunLight sun_lights[MAX_SUN_LIGHTS];
    PointLight point_lights[MAX_POINT_LIGHTS];
    SpotLight spot_lights[MAX_SPOT_LIGHTS];
    
    int num_sun_lights;
    int num_point_lights;
    int num_spot_lights;
};

// layout(location = 0)uniform float time;

float calcSunLight(SunLight light, vec3 normal, vec3 position){   
    return 1.5*max(dot(normalize(normal),normalize(position + light.angle.xyz)),0.0);
}

float calcPointLight(PointLight light, vec3 normal, vec3 position) {
    vec3 lightDir = normalize(light.position.xyz - position);
    float strength = max(dot(normalize(normal),normalize(lightDir)),0.0);
    float dist = length(light.position.xyz - position);

    float constant = light.attentuation.x;
    float linear = light.attentuation.y;
    float quadratic = light.attentuation.z;

    float attentuation = 1.0 / (constant + (linear * dist) + quadratic * ( dist * dist));
    return attentuation*strength;
}

void main()
{   
    float depth = length(view_pos - position_f);

    vec2 cord = gl_FragCoord.xy;

    float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength*vec3(0.749, 0.6706, 0.8157);

    float diffuseStrength = 1.0f; //max(dot(normalize(normal_f),normalize(-position_f + vec3(0.0,0.0,0.0))),0.0);
    // vec3 color = color_texture()
    vec4 diffuse;

    vec2 flowDirection = vec2(0.0,-0.08);
    float transparency = alpha;

    if((available_textures & 128u) > 0u) {
        transparency = texture(color_texture, uv_f).a;
        diffuse = diffuseStrength*texture(color_texture, uv_f+time*flowDirection).rgba;
    } else {
        diffuse = diffuseStrength*vec4(0.7412, 0.7412, 0.7412,1.0);
    }
    // fragmentColor = vec4(sin(nu.x*0.1)*0.5+0.5,cos(nu.y*0.1)*0.5+0.5,0.1,1.0f);
    vec3 color = (ambient + diffuse.rgb)*vec3(0.78, 0.79, 0.71);

    if(fog) {
        float f = exp(-0.28*depth);
        color = (f)*color + (1.0-f)*vec3(0.7922, 0.7804, 0.7804);
    }

    fragmentColor = vec4(color.rgb, transparency);
        
}

