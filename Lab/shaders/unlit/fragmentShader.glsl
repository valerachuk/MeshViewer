#version 330 core

uniform vec3 customColor;
out vec4 color;

void main()
{
	color = vec4(customColor, 1.0f);
}