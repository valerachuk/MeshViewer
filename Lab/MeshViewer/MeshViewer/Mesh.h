#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <vector>
#include "iostream"
#include "Vertex.h"

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertices, bool isDefaultColor = true, glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f));
	~Mesh();

	void setColor(glm::vec3);
	void setPosition(glm::vec3 inPos);
	void translate(glm::vec3 delta);
	void rotate(glm::vec3 vector, float angle);

	glm::vec3 getColor();
	glm::vec3 getWorldPosition();
	const GLuint& getVao();
	GLuint getVertexCount();
	bool isColorDefault();
	glm::mat4 calcWorldMatrix();

private:
	GLuint VAO, VBO;
	GLuint vertexCount;

	glm::vec3 color;
	glm::vec3 centerMass;
	bool isDefaultColor;

	glm::vec3 worldPosition;
	glm::mat4 roationMatrix;
	float fitFactor;

	void loadMeshToGpu(const std::vector<Vertex>& vertices);
	float calcFitFactor(const std::vector<Vertex>& vertices, float maxSize);
	glm::vec3 calcCenterMass(const std::vector<Vertex>& vertices);
};