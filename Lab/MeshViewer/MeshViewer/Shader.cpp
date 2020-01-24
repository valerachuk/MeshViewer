#include "Shader.h"

std::string Shader::ReadFile(const char* path)
{
    std::ifstream file(path);
    std::string shaderString;
    std::stringstream sstream;

    if (!file.is_open()) {
        throw new std::runtime_error("Can't open the file!");
    }

    sstream << file.rdbuf();
    shaderString = sstream.str();
    shaderString.push_back(0);
    file.close();

    return shaderString;
}

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) : shaderProgram(0)
{
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    std::string stupudString = ReadFile(vertexPath);
    const GLchar* vertexShaderFile = stupudString.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderFile, NULL);
    glCompileShader(vertexShader);

    stupudString = ReadFile(fragmentPath);
    const GLchar* fragmentShaderFile = stupudString.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderFile, NULL);
    glCompileShader(fragmentShader);

    GLint successVertex;
    GLchar infoLogVertex[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);
    if (!successVertex) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLogVertex);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogVertex << std::endl;
        exit(-1);
    }

    GLint successFragment;
    GLchar infoLogFragment[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);
    if (!successFragment) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogFragment);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogFragment << std::endl;
        exit(-1);
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::UseProgram() const{
	glUseProgram(shaderProgram);
}

void Shader::setMat4Uniform(const char* name, const glm::mat4& matrix4)
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, glm::value_ptr(matrix4));
}

void Shader::setVec3Uniform(const char* name, const glm::vec3& vector3)
{
    glUniform3fv(glGetUniformLocation(shaderProgram, name), 1, glm::value_ptr(vector3));
}

void Shader::setFloatUniform(const char* name, const float& value)
{
    glUniform1f(glGetUniformLocation(shaderProgram, name), value);
}

void Shader::setBoolUniform(const char* name, const bool& value)
{
    glUniform1i(glGetUniformLocation(shaderProgram, name), value);
}
