#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

uniform mat4 projection;
uniform mat4 model;

out vec2 TexCoords;

void main()
{
    gl_Position = projection * model * vec4(position, 1.0f);
    TexCoords = texCoords;
}