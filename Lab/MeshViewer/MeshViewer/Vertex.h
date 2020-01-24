#pragma once
#include <glm\glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;

	Vertex(glm::vec3 position, glm::vec3 normal) : position(position), normal(normal) {}
};