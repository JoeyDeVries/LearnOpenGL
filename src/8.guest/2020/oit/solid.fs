#version 400 core

// shader outputs
layout (location = 0) out vec4 frag;

// material color
uniform vec3 color;

void main()
{
	frag = vec4(color, 1.0f);
}