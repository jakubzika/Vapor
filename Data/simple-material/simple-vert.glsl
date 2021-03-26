#version 330
#extension GL_ARB_explicit_uniform_location : require

in vec3 position;
in vec3 normal;
in vec2 uv;

uniform float time;
layout(location = 10) uniform mat4 PVM;

out vec4 color;

void main()
{
  float time_a = time/50;
  

  gl_Position = PVM*vec4(position,1.0);

  float offset = sin(time_a);

  color.rgb = vec3(position.x/60+0.5,position.y/60,position.z/60+0.5);  
}
