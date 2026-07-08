#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform vec3 lightDir;
uniform vec3 viewDir;

void main()
{
    // ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * vec3(texture(texture1, TexCoords));
  
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(-lightDir);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * vec3(texture(texture1, TexCoords));
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDirection = normalize(viewDir);
    vec3 reflectDir = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * vec3(1.0) * spec;
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
