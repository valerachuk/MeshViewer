#pragma once
#include <glm\glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;

	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec3 color) : position(position), normal(normal), color(color) {}
};