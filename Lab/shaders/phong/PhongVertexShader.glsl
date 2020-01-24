#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 fragPos;
out vec3 fragNormal;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main()
{
    gl_Position = projMatrix * viewMatrix * worldMatrix * vec4(position, 1.0);
    fragPos = vec3(worldMatrix * vec4(position, 1.0f));
    fragNormal = vec3(worldMatrix * vec4(normal, 0.0f));
}