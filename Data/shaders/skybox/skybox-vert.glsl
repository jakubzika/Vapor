#version 330
#extension GL_ARB_explicit_uniform_location : require

in vec3 position;
in vec3 normal;
in vec2 uv;


out vec3 normal_f;
out vec2 uv_f;
out vec3 position_f;


layout(location = 10) uniform mat4 projection;
layout(location = 30) uniform mat4 view;

void main()
{
    position_f = position;
    vec4 pos = projection * mat4(mat3(view)) * vec4(position, 1.0);
    gl_Position = pos.xyzw;
}