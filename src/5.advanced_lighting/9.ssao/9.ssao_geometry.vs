#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

uniform bool invertedNormals;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 viewPos = view * model * vec4(aPos, 1.0);
    FragPos = viewPos.xyz; 
    TexCoords = aTexCoords;
    
    mat3 normalMatrix = transpose(inverse(mat3(view * model)));
    Normal = normalMatrix * (invertedNormals ? -aNormal : aNormal);
    
    gl_Position = projection * viewPos;
}