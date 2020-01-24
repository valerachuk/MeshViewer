#include "GLRenderSystem.h"

GLRenderSystem::GLRenderSystem() :
	worldMatrix(glm::mat4(1.0f)),
	projMatrix(glm::mat4(1.0f)),
	viewMatrix(glm::mat4(1.0f)),
	isDefaultColor(true),
	customColor(glm::vec3(1.0f)),
	cameraPos(glm::vec3(1.0f)),
	shaderProgram(nullptr),
	renderMode(RenderMode::Triangles)
{
	setupLight(glm::vec3(0), 0, 0, 0);
}

void GLRenderSystem::init()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void GLRenderSystem::clearDisplay(float red, float green, float blue)
{
	glClearColor(red, green, blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRenderSystem::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t heigth)
{
	glViewport(x, y, width, heigth);
}

void GLRenderSystem::render(GLuint VAO, GLuint verticesCount)
{
	if (renderMode == RenderMode::Triangles)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		renderVertices(VAO, verticesCount);
	}
	else 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		renderVertices(VAO, verticesCount);
	}
}

void GLRenderSystem::setupLight(glm::vec3 position, float Ia, float Id, float Is)
{
	lightPos = position;
	ambientStrength = Ia;
	diffuseStrength = Id;
	specularStrength = Is;
}

void GLRenderSystem::setCameraPos(glm::vec3 position)
{
	cameraPos = position;
}

void GLRenderSystem::setWorldMatrix(const glm::mat4& matrix)
{
	worldMatrix = matrix;
}

const glm::mat4& GLRenderSystem::getWorldMatrix() const
{
	return worldMatrix;
}

void GLRenderSystem::setViewMatrix(const glm::mat4& matrix)
{
	viewMatrix = matrix;
}

const glm::mat4& GLRenderSystem::getViewMatrix() const
{
	return viewMatrix;
}

void GLRenderSystem::setProjMatrix(const glm::mat4& matrix)
{
	projMatrix = matrix;
}

const glm::mat4& GLRenderSystem::getProjMatrix() const
{
	return projMatrix;
}

void GLRenderSystem::setColor(const glm::vec3& color)
{
	customColor = color;
}

const glm::vec3& GLRenderSystem::getCustomColor()
{
	return customColor;
}

void GLRenderSystem::setShaderProgram(Shader& shader)
{
	shaderProgram = &shader;
}

Shader* GLRenderSystem::getShaderProgram()
{
	return shaderProgram;
}

RenderMode GLRenderSystem::getRenderMode()
{
	return renderMode;
}

void GLRenderSystem::setRenderMode(RenderMode mode)
{
	renderMode = mode;
}

void GLRenderSystem::sendUniformsToShader()
{
	if (shaderProgram != nullptr)
	{
		shaderProgram->setMat4Uniform("worldMatrix", getWorldMatrix());
		shaderProgram->setMat4Uniform("viewMatrix", getViewMatrix());
		shaderProgram->setMat4Uniform("projMatrix", getProjMatrix());
		shaderProgram->setVec3Uniform("customColor", getCustomColor());

		shaderProgram->setFloatUniform("ambientStrength", ambientStrength);
		shaderProgram->setFloatUniform("diffuseStrength", diffuseStrength);
		shaderProgram->setFloatUniform("specularStrength", specularStrength);
		shaderProgram->setVec3Uniform("lightPos", lightPos);
		shaderProgram->setVec3Uniform("camPos", cameraPos);
	}
}

void GLRenderSystem::renderVertices(GLuint VAO, GLuint verticesCount)
{
	glBindVertexArray(VAO);

	shaderProgram->UseProgram();
	sendUniformsToShader();

	glDrawArrays(GL_TRIANGLES, 0, verticesCount);
	glBindVertexArray(0);
}
