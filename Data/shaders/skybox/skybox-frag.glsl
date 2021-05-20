#version 330
#extension GL_ARB_explicit_uniform_location : require
#extension GL_EXT_gpu_shader4 : enable

out vec4 fragmentColor;

layout(location = 114)uniform bool fog;

in vec3 position_f;
in vec3 normal_f;
in vec2 uv_f;


layout(location = 97)uniform samplerCube skybox_texture;

void main() {
    if(fog) {
    fragmentColor = vec4(vec3(0.7922, 0.7804, 0.7804),1.0);

    } else {
        fragmentColor = texture(skybox_texture,position_f);
    }
}
