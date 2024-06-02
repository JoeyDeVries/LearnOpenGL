#version 330 core

// Input variables from the vertex shader
in vec4 FragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform vec3 lightPos;
uniform float far_plane;

void main()
{
    float lightDistance = length(FragPos.xyz - lightPos);
    
    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / far_plane;
    
    // write this as modified depth
    gl_FragDepth = lightDistance;
}