#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, bool isDefaultColor, glm::vec3 color):
	VBO(0),
	VAO(0),
	color(color), 
	isDefaultColor(isDefaultColor),
	vertexCount(vertices.size()),
	worldPosition(glm::vec3(0.0f)),
	roationMatrix(glm::mat4(1.0f)),
	centerMass(glm::vec3(0.0f)),
	fitFactor(1)
{
	loadMeshToGpu(vertices);
	vertexCount = vertices.size();
	centerMass = calcCenterMass(vertices);
	fitFactor = calcFitFactor(vertices, 1);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

glm::vec3 Mesh::getColor()
{
	return color;
}

glm::vec3 Mesh::getWorldPosition()
{
	return worldPosition;
}

void Mesh::setColor(glm::vec3 inColor)
{
	color = inColor;
}

void Mesh::setPosition(glm::vec3 inPos)
{
	worldPosition = inPos;
}

void Mesh::translate(glm::vec3 delta)
{
	worldPosition += delta;
}

void Mesh::rotate(glm::vec3 vector, float angle)
{
	roationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vector) * roationMatrix;
}

const GLuint& Mesh::getVao()
{
	return VAO;
}


GLuint Mesh::getVertexCount()
{
	return vertexCount;
}

bool Mesh::isColorDefault()
{
	return isDefaultColor;
}

glm::mat4 Mesh::calcWorldMatrix()
{
	glm::mat4 matrix(1.0f);
	matrix = glm::translate(matrix, worldPosition);
	matrix = glm::scale(matrix, glm::vec3(1.0f) * fitFactor);
	matrix = matrix * roationMatrix;
	matrix = glm::translate(matrix, -centerMass);
	return matrix;
}

void Mesh::loadMeshToGpu(const std::vector<Vertex>& vertices)
{
	GLfloat* vertexArray = verticesToArray(vertices);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * 9 * sizeof(float), vertexArray, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	delete[] vertexArray;
}

float Mesh::calcFitFactor(const std::vector<Vertex>& vertices, float maxSize)
{
	float maxRadius = 0;

	for (uint32_t i = 0; i < vertices.size(); i++)
	{
		float length = glm::length(centerMass - vertices[i].position);
		if (length > maxRadius)
		{
			maxRadius = length;
		}
	}

	return maxSize / maxRadius;
}

glm::vec3 Mesh::calcCenterMass(const std::vector<Vertex>& vertices)
{
	float toatalArea = 0;
	glm::vec3 sum(0.0f);

	for (uint32_t i = 0; i < vertices.size(); i += 3)
	{

		const glm::vec3& pntA = vertices[i].position;
		const glm::vec3& pntB = vertices[i + 1].position;
		const glm::vec3& pntC = vertices[i + 2].position;

		glm::vec3 currentCenter = (pntA + pntB + pntC) / 3.0f;

		float currentArea = glm::length(glm::cross(pntB - pntA, pntC - pntA)) / 2.0f;
		sum += currentCenter * currentArea;
		toatalArea += currentArea;
	}

	return sum / toatalArea;
}

float* Mesh::verticesToArray(const std::vector<Vertex>& vertices)
{
	int vectorSize = vertices.size();
	if (vectorSize % 3 != 0)
	{
		throw new std::invalid_argument("Vertices size % 3 must be equals 0!");
	}

	float* vertexArray = new float[vectorSize * 9];
	for (int32_t vectorCnt = 0, arrayCnt = 0; vectorCnt < vectorSize; vectorCnt++, arrayCnt += 9)
	{
		vertexArray[arrayCnt] = vertices[vectorCnt].position.x;
		vertexArray[arrayCnt + 1] = vertices[vectorCnt].position.y;
		vertexArray[arrayCnt + 2] = vertices[vectorCnt].position.z;

		vertexArray[arrayCnt + 3] = vertices[vectorCnt].normal.x;
		vertexArray[arrayCnt + 4] = vertices[vectorCnt].normal.y;
		vertexArray[arrayCnt + 5] = vertices[vectorCnt].normal.z;

		vertexArray[arrayCnt + 6] = vertices[vectorCnt].color.r;
		vertexArray[arrayCnt + 7] = vertices[vectorCnt].color.g;
		vertexArray[arrayCnt + 8] = vertices[vectorCnt].color.b;

	}

	return vertexArray;
}
