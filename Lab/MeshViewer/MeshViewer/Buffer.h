#pragma once
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"
#include <iostream>

class Buffer {
public:
	Buffer(const std::vector<Vertex>& vertices);
	~Buffer();

	const GLuint& getVAO() const;
	const GLuint& getVertexCount() const;
	const std::vector<Vertex>& getVertices() const;;

private:
	GLuint VAO, VBO;
	size_t vertexCount;
	const std::vector<Vertex> vertexVector;

};