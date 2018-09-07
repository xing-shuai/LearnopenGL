#pragma once
#include <GL/glew.h>
#include <string>


class GLSLProgram {
public:
	GLSLProgram();
	virtual ~GLSLProgram();

	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

	void linkShaders();

	void addAttribute(const std::string& attributeName);

	void use();
	void unuse();

	GLint getUniformLocation(const std::string& uniformName);

private:

	void compileShader(const std::string& filePath, GLuint id);

	GLuint _programID;

	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	int _numAttributes;
};