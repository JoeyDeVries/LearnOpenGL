#version 330 core

out vec4 FragColor;

in float Height;

void main()
{
    float h = (Height + 16)/32.0f;	// shift and scale the height in to a grayscale value
    FragColor = vec4(h, h, h, 1.0);
}