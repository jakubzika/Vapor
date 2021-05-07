#version 330
#extension GL_ARB_explicit_uniform_location : require

in vec3 position;
in vec3 normal;
in vec2 uv;

out vec3 normal_f;
out vec2 uv_f;
out vec3 position_f;

uniform float time;
layout(location = 10) uniform mat4 projection;
layout(location = 30) uniform mat4 view;
layout(location = 50) uniform mat4 model;
layout(location = 70) uniform mat3 PVM_inverse;

out vec4 color;

void main()
{
  float time_a = time/50;
  

  gl_Position = projection*view*model*vec4(position,1.0);

  uv_f = uv;
  position_f = (model*vec4(position,1.0)).xyz;
  normal_f = PVM_inverse*normal;

  float offset = sin(time_a);

  color.rgb = vec3(position.x/60+0.5,position.y/60,position.z/60+0.5);  
}
