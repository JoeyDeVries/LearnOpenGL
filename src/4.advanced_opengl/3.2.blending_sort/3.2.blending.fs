#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture1;

void main()
{             
    color = texture(texture1, TexCoords);
} 