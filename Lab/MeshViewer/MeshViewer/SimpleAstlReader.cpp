#include "SimpleAstlReader.h"

SimpleAstlReader::SimpleAstlReader(const char* path)
{
	fileStream = std::ifstream(path);
	assert(fileStream.is_open());
	vertices = std::vector<Vertex>();
	readSolid();
	fileStream.close();
}

std::vector<Vertex>& SimpleAstlReader::getVertices()
{
	return vertices;
}

glm::vec3& SimpleAstlReader::readVec3()
{
	glm::vec3 vector(0.0f);

	fileStream >> vector.x;
	fileStream >> vector.y;
	fileStream >> vector.z;

	return vector;
}

void SimpleAstlReader::readFacet()
{
	glm::vec3 normal(0.0f);
	std::string skip;
	fileStream >> skip;

	if (skip != "normal")
		throw "normal keyword is missing";

	normal = readVec3();

	fileStream >> skip;
	if (skip != "outer")
		throw std::runtime_error("outer keyword is missing");

	fileStream >> skip;
	if (skip != "loop")
		throw std::runtime_error("loop keyword is missing");

	glm::vec3 points[3];
	for (int i = 0; i < 3; i++)
	{
		fileStream >> skip;
		if (skip != "vertex")
			throw std::runtime_error("vertex keyword is missing");
		points[i] = readVec3();
	}
	fileStream >> skip;
	if (skip != "endloop")
		throw std::runtime_error("endloop keyword is missing");

	fileStream >> skip;
	if (skip != "endfacet")
		throw std::runtime_error("endfacet keyword is missing");

	for (int i = 0; i < 3; i++)
	{
		vertices.push_back(Vertex(points[i], normal, glm::vec3(1.0f, 0.0f, 0.0f)));
	}
}

void SimpleAstlReader::readSolid()
{
	std::string skip;
	fileStream >> skip;
	if (skip != "solid")
		throw std::runtime_error("solid keyword is missing");

	fileStream >> skip; //skip solid name

	while (true)
	{
		fileStream >> skip;
		if (skip == "endsolid" || fileStream.eof())
			return;
		if (skip != "facet")
			throw std::runtime_error("facet keyword is missing");

		readFacet();
	}

}
