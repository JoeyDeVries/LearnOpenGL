#version 420 core

// shader inputs
layout (location = 0) in vec3 position;

void main()
{
	gl_Position = vec4(position, 1.0f);
}