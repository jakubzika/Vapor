#version 330
out vec4 fragmentColor;

in vec3 position_f;
in vec3 normal_f;
in vec2 uv_f;
// layout(location = 0)uniform float time;

void main()
{   
    vec2 cord = gl_FragCoord.xy;
    
    vec2 new;
    new.x = cos(1.2)*cord.x - sin(1.2)*cord.y;
    new.y = sin(1.2)*cord.x + cos(1.2)*cord.y;


    float ambientStrenght = 0.3f;
    vec3 ambient = ambientStrenght*vec3(0.749, 0.6706, 0.8157);

    float diffuseStrenght = max(dot(normalize(normal_f),normalize(-position_f + vec3(0.0,0.0,0.0))),0.0);
    vec3 diffuse = diffuseStrenght*vec3(0.7412, 0.7412, 0.7412);
    // fragmentColor = vec4(sin(nu.x*0.1)*0.5+0.5,cos(nu.y*0.1)*0.5+0.5,0.1,1.0f);
    vec3 color = (ambient + diffuse)*vec3(0.9725, 0.9725, 0.9725);
    fragmentColor = vec4(color,1.0);
        
}

