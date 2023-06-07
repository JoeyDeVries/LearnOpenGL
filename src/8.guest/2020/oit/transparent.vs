#version 420 core

// shader inputs
layout (location = 0) in vec3 position;

// model * view * projection matrix
uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(position, 1.0f);
}