#version 330 core
out vec4 FragColor;
in vec3 WorldPos;

uniform samplerCube environmentMap;
uniform float lod;

void main()
{		
    // vec3 envColor = textureLod(environmentMap, WorldPos, 1.0).rgb;
    vec3 envColor = textureLod(environmentMap, WorldPos, lod).rgb;
    
    // HDR tonemap and gamma correct
    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2)); 
    
    FragColor = vec4(envColor, 1.0);
}
