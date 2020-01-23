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
	void translate(glm::vec3 delta);
	void rotate(glm::vec3 vector, float angle);

	const Buffer& getBuffer() const;

	glm::vec3 getWorldPosition();
	glm::mat4 calcWorldMatrix();

private:
	std::shared_ptr<Buffer> bufferPtr;

	glm::vec3 centerMass;

	glm::vec3 worldPosition;
	glm::mat4 roationMatrix;
	float fitFactor;

	float calcFitFactor(const std::vector<Vertex>& vertices, float maxSize);
	glm::vec3 calcCenterMass(const std::vector<Vertex>& vertices);
};