#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexcoord;

uniform mat4 model;
uniform mat3 normalMatrix;
uniform mat4 view;
uniform mat4 projection;

out vec3 worldPosition;
out vec3 worldNormal;
out vec2 texcoord;

void main()
{
	vec4 worldpos = model * vec4(aPosition, 1.0f);
	worldPosition = worldpos.xyz;
	worldNormal = normalMatrix * aNormal;
	texcoord = aTexcoord;

	gl_Position = projection * view * worldpos;
}
