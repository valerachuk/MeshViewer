#include "Buffer.h"

Buffer::Buffer(const std::vector<Vertex>& vertices) : vertexVector(vertices)
{
	vertexCount = vertexVector.size();

	if (vertices.size() <= 0 || vertices.size() % 3 != 0)
	{
		throw new std::invalid_argument("Vertices size % 3 must be equals 0!");
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * 9 * sizeof(GLfloat), &vertexVector[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

}

Buffer::~Buffer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

const GLuint& Buffer::getVAO() const
{
	return VAO;
}

const GLuint& Buffer::getVertexCount() const
{
	return vertexCount;
}

const std::vector<Vertex>& Buffer::getVertices() const
{
	return vertexVector;
}
