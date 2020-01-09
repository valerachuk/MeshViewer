#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <GL\glew.h>

class Shader {
private:
	std::string ReadFile(const GLchar* path);
	GLuint shaderProgram;

public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void UseProgram() const;

	void setMat4Uniform(const char* name, const glm::mat4& matrix4);
	void setVec3Uniform(const char* name, const glm::vec3& vector3);
	void setFloatUniform(const char* name, const float& value);
	void setBoolUniform(const char* name, const bool& value);
};