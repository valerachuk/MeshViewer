#pragma once
#include <iostream>
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Shader.h"
#include "Vertex.h"

class GLRenderSystem
{
public:
	GLRenderSystem();

	static void init();
	static void clearDisplay(float red, float green, float blue);
	static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t heigth);

	void renderTriangleSoup(GLuint VAO, GLuint verticesCount);
	void renderLines(GLuint VAO, GLuint verticesCount);
	
	void setupLight(glm::vec3 position, float Ia, float Id, float Is);
	void setCameraPos(glm::vec3 position);

	void setWorldMatrix(const glm::mat4& matrix);
	const glm::mat4& getWorldMatrix() const;

	void setViewMatrix(const glm::mat4& matrix);
	const glm::mat4& getViewMatrix() const;

	void setProjMatrix(const glm::mat4& matrix);
	const glm::mat4& getProjMatrix() const;

	void setCustomColor(const glm::vec3& color);
	const glm::vec3& getCustomColor();

	void setIsDefaultColor(bool isDefault);
	bool getIsDefaultColor();

	void setShaderProgram(Shader&);
	Shader* getShaderProgram();

private:
	glm::mat4 worldMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
	glm::vec3 customColor;
	bool isDefaultColor;

	glm::vec3 lightPos;
	glm::vec3 cameraPos;
	float ambientStrength, diffuseStrength, specularStrength;

	Shader* shaderProgram;

	void sendUniformsToShader();
	void renderVertices(GLuint VAO, GLenum mode, GLuint verticesCount);
};