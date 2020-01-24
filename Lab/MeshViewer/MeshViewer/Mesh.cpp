#include "Mesh.h"

Mesh::Mesh(std::shared_ptr<Buffer> buffer):
	bufferPtr(buffer),
	worldPosition(glm::vec3(0.0f)),
	transform(glm::mat4(1.0f)),
	centerMass(glm::vec3(0.0f)),
	fitFactor(1)
{
	centerMass = calcCenterMass(bufferPtr->getVertices());
	fitFactor = calcFitFactor(bufferPtr->getVertices(), 1);
}

const glm::vec3& Mesh::getWorldPosition() const
{
	return worldPosition;
}

void Mesh::setPosition(glm::vec3 inPos)
{
	worldPosition = inPos;
}

void Mesh::rotate(glm::vec3 vector, float angle)
{
	transform = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vector) * transform;
}

const Buffer& Mesh::getBuffer() const
{
	return *bufferPtr;
}

glm::mat4 Mesh::calcWorldMatrix()
{
	glm::mat4 matrix(1.0f);
	matrix = glm::translate(matrix, worldPosition);
	matrix = glm::scale(matrix, glm::vec3(1.0f) * fitFactor);
	matrix = matrix * transform;
	matrix = glm::translate(matrix, -centerMass);
	return matrix;
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
	float toatalAreaX2 = 0;
	glm::vec3 sumX6(0.0f);

	for (uint32_t i = 0; i < vertices.size(); i += 3)
	{
		const glm::vec3& pntA = vertices[i].position;
		const glm::vec3& pntB = vertices[i + 1].position;
		const glm::vec3& pntC = vertices[i + 2].position;

		glm::vec3 currentCenterX3 = pntA + pntB + pntC;

		float currentAreaX2 = glm::length(glm::cross(pntB - pntA, pntC - pntA));
		sumX6 += currentCenterX3 * currentAreaX2;
		toatalAreaX2 += currentAreaX2;
	}

	return sumX6 / toatalAreaX2 / 3.0f;
}