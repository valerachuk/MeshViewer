#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec3 fragColor;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform vec3 customColor;
uniform bool isDefaultColor;

void main()
{
    gl_Position = projMatrix * viewMatrix * worldMatrix * vec4(position, 1.0);
    
    if (isDefaultColor)
    {
        fragColor = color;
    }
    else
    {
        fragColor = customColor;
    }
}