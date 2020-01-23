#pragma once	
#include <glm\glm.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "Vertex.h"
#include <assert.h>

class SimpleAstlReader
{
public:
	SimpleAstlReader(const char* path);
	std::vector<Vertex>& getVertices();

private:
	std::ifstream fileStream;
	std::vector<Vertex> vertices;

	glm::vec3& readVec3();
	void readFacet();
	void readSolid();
};