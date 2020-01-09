#pragma once	
#include <glm\glm.hpp>
#include <vector>
#include <fstream>
#include "Vertex.h"

class SimpleAstlReader
{
public:
	static std::vector<Vertex>& getVertices(const char* path);
	
private:
	static std::istream& readVec3(std::istream& in, glm::vec3& vector);
	static std::istream& readFacet(std::istream& in, std::vector<Vertex>& vertices);
	static std::istream& readSolid(std::istream& in, std::vector<Vertex>& vertices);
};