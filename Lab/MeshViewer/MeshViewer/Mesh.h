#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include "Vertex.h"
#include "Buffer.h"

class Mesh
{
public:
	Mesh(std::shared_ptr<Buffer>);

	void setPosition(glm::vec3 inPos);
	void rotate(glm::vec3 vector, float angle);

	const Buffer& getBuffer() const;

	const glm::vec3& getWorldPosition() const;
	glm::mat4 calcWorldMatrix();

	float getOuterRadius();

private:
	std::shared_ptr<Buffer> bufferPtr;

	glm::vec3 centerMass;
	glm::vec3 worldPosition;
	glm::mat4 transform;
	float outerRadius;

	float calcOuterRadius(const std::vector<Vertex>& vertices, const glm::vec3& inPos);
	glm::vec3 calcCenterMass(const std::vector<Vertex>& vertices);
};