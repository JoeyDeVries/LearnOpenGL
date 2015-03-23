#version 330 core
out vec4 color;

float LinearizeDepth(float depth) // Note that this ranges from [0,1] instead of up to 'far plane distance' since we divide by 'far'
{
    float near = 0.1; 
    float far = 100.0; 
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near) / (far + near - z * (far - near));	
}

void main()
{             
    float depth = LinearizeDepth(gl_FragCoord.z);
    color = vec4(vec3(depth), 1.0f);
}