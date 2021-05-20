#version 420
#extension GL_ARB_explicit_uniform_location : require
#extension GL_EXT_gpu_shader4 : enable

out vec4 fragmentColor;

in vec3 position_f;
in vec3 normal_f;
in vec2 uv_f;

layout(location = 112)uniform float time;

layout(location = 2)uniform bool animated;
layout(location = 3)uniform uint num_frames;
layout(location = 4)uniform float frame_length;
layout(location = 5)uniform float frame_width;

layout(location = 110)uniform float roughness;
layout(location = 111)uniform float metalness;
layout(location = 113)uniform float alpha;
layout(location = 114)uniform bool fog;

layout(location =6)uniform vec3 view_pos;

layout(location = 90)uniform uint available_textures;
layout(location = 91)uniform sampler2D color_texture;
layout(location = 92)uniform sampler2D normal_texture;
layout(location = 93)uniform sampler2D specular_texture;
layout(location = 94)uniform sampler2D roughness_texture;
layout(location = 95)uniform sampler2D metalness_texture;
layout(location = 96)uniform sampler2D reflection_texture;
layout(location = 97)uniform samplerCube skybox_texture;
layout(location = 98)uniform samplerCube irradiance_texture;

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

vec3 calcSunLight(SunLight light, vec3 normal, vec3 position, vec2 uv, vec3 view_direction, vec3 color){
    
    // vec3 reflect_direction = reflect(-light.angle.xyz, normal);  

    // float specular = pow(max(dot(view_direction, reflect_direction), 0.0), 32);
    
    // return max(dot(normalize(normal),normalize(position + light.angle.xyz)),0.0) + light.strength*specular;

    vec3 light_direction = normalize(-light.angle.xyz);
    // diffuse shading
    float diff = max(dot(normal, light_direction), 0.0);
    // specular shading
    vec3 reflect_direction = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), roughness);
    // combine results
    vec3 ambient  = vec3(color)*0.2;
    vec3 diffuse  = diff * vec3(color)*0.3;
    vec3 specular = spec * vec3(0.2);
    return (ambient + diffuse + specular)*vec3(light.color)*0.5;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 position, vec2 uv, vec3 view_direction, vec3 color) {


    vec3 light_direction = normalize(light.position.xyz - position);
    // diffuse shading
    float diff = max(dot(normal, light_direction), 0.0);
    // specular shading
    vec3 reflect_direction = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), 1.0);
    // attenuation
    float distance    = length(light.position.xyz - position);
    float attenuation = 1.0 / (light.attentuation.x + light.attentuation.y * distance + 
  			     light.attentuation.z * (distance * distance));    
    // combine results
    vec3 ambient  = vec3(color)*0.05;
    vec3 diffuse  = diff * vec3(color)*0.8;
    vec3 specular = spec * color * vec3(color) * 1.0;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular)* light.color.xyz * 0.3;
}

vec3 calcSpotLight(SpotLight light,vec3 normal, vec3 position, vec2 uv, vec3 view_direction, vec3 color) {
    vec3 light_direction = normalize(light.position.xyz - position);

    float theta     = dot(light_direction, normalize(-light.angle.xyz));
    float epsilon   = light.cone.x - light.cone.y;
    float intensity = clamp((theta - light.cone.y) / epsilon, 0.0, 1.0);

   return intensity * color * light.color.xyz*0.2;
}

void main()
{   
    float depth = length(view_pos - position_f);
    vec3 view_direction = normalize(view_pos - position_f);
    vec2 cord = gl_FragCoord.xy;

    vec3 norm = normalize(normal_f);

    // vec3 color = color_texture()

    vec2 uv_frame = uv_f;
    if(animated) {
        uint frame_idx = uint(time/frame_length)%num_frames;
        uv_frame.x += frame_idx * frame_width;
    }

    float transparency = alpha;
    vec4 color_texture_color = vec4(0.5725, 0.4824, 0.1137, 1.0);

    

    if((available_textures & 128u) > 0u) {    
        color_texture_color = texture(color_texture,uv_frame);
        transparency *= color_texture_color.a;
    }


    if(transparency == 0.0) discard;

    vec3 color = color_texture_color.rgb*0.2;
    for(int i = 0; i < num_sun_lights; i++) {
        color += calcSunLight(sun_lights[i], norm, position_f, uv_frame, view_direction, color_texture_color.rgb);
    }

    for(int i = 0; i < num_point_lights; i++) {
        color += calcPointLight(point_lights[i], normal_f, position_f,uv_frame, view_direction, color_texture_color.rgb);
    }

    for(int i = 0; i < num_spot_lights; i++) {
        color += calcSpotLight(spot_lights[i], normal_f, position_f,uv_frame, view_direction, color_texture_color.rgb);
    }

    // if((available_textures & 128u) > 0u) {
    //     transparency = texture(color_texture, uv_frame).a;
    //     diffuse = diffuseStrength*texture(color_texture, uv_frame);
    // } else {
    //     diffuse = diffuseStrength*vec4(0.7412, 0.7412, 0.7412,1.0);
    // }
    // fragmentColor = vec4(sin(nu.x*0.1)*0.5+0.5,cos(nu.y*0.1)*0.5+0.5,0.1,1.0f);
    // vec4 color = (vec4(ambient,1.0) + diffuse)*vec4(0.78, 0.79, 0.71,1.0);

    
    if((available_textures & 2u) > 0u) {
        vec3 I = normalize(position_f - view_pos);
        vec3 R = reflect(I, normalize(normal_f));
        color += vec3(texture(skybox_texture, R).rgb)*0.3*(1.0-roughness/100.0);
    }
    
    if(fog) {
        float f = exp(-0.28*depth);
        color = (f)*color + (1.0-f)*vec3(0.7922, 0.7804, 0.7804);
    }

    fragmentColor = vec4(color.rgb, max(transparency,0.0));

    

    // float gamma = 2.2;
    // fragmentColor.rgb = pow(fragmentColor.rgb, vec3(1.0/gamma));
    
}

