#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;

void main()
{
    vec4 worldPos = model * vec4(aPos, 1.0);
    gl_Position = worldPos;

    
}