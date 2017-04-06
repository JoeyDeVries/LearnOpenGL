#version 330 core
out vec4 fragColor;

in vec3 ourColor;
in vec2 texCoord;

// texture sampler
uniform sampler2D texture1;

void main()
{
	fragColor = texture(texture1, texCoord);
}