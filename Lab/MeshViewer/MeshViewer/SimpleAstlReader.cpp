#include "SimpleAstlReader.h"

std::vector<Vertex>& SimpleAstlReader::getVertices(const char* path)
{
	std::ifstream file(path);
	std::vector<Vertex>* vertices = new std::vector<Vertex>();
	readSolid(file, *vertices);
	vertices->shrink_to_fit();
	file.close();
	return *vertices;
}

std::istream& SimpleAstlReader::readVec3(std::istream& in, glm::vec3& vector)
{
	in >> vector.x;
	in >> vector.y;
	in >> vector.z;
	return in;
}

std::istream& SimpleAstlReader::readFacet(std::istream& in, std::vector<Vertex>& vertices)
{
	glm::vec3 normal(0.0f);
	std::string skip;
	in >> skip;
	if (skip != "normal")
		throw "normal keyword is missing";

	readVec3(in, normal);

	in >> skip;
	if (skip != "outer")
		throw std::runtime_error("outer keyword is missing");
	in >> skip;
	if (skip != "loop")
		throw std::runtime_error("loop keyword is missing");

	glm::vec3 points[3];
	for (int i = 0; i < 3; i++)
	{
		in >> skip;
		if (skip != "vertex")
			throw std::runtime_error("vertex keyword is missing");
		readVec3(in, points[i]);
	}
	in >> skip;
	if (skip != "endloop")
		throw std::runtime_error("endloop keyword is missing");

	in >> skip;
	if (skip != "endfacet")
		throw std::runtime_error("endfacet keyword is missing");

	for (int i = 0; i < 3; i++)
	{
		vertices.push_back(Vertex(points[i], normal, glm::vec3(0.0f, 0.0f, 0.0f)));
	}

	return in;
}

std::istream& SimpleAstlReader::readSolid(std::istream& in, std::vector<Vertex>& vertices)
{
	std::string skip;
	in >> skip;
	if (skip != "solid")
		throw std::runtime_error("solid keyword is missing");

	in >> skip; //skip solid name

	for (;;)
	{
		in >> skip;
		if (skip == "endsolid" || in.eof())
			return in;
		if (skip != "facet")
			throw std::runtime_error("facet keyword is missing");

		readFacet(in, vertices);
	}

	return in;
}
