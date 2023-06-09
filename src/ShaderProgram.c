#include "ShaderProgram.h"
#include "Utils.h"
#include <glad/gl.h>

void checkForErrors(unsigned int id, int status)
{
	int success;
	char infoLog[512];

	if(status == GL_COMPILE_STATUS)
	{
		glGetShaderiv(id, status, &success);

		if(!success)
		{
			glGetShaderInfoLog(id, 512, NULL, infoLog);
			log_error("Error in Compiling Shader\n%s\n", infoLog);
			exit(EXIT_FAILURE);
		}
	}
	else if(status == GL_LINK_STATUS)
	{
		glGetProgramiv(id, status, &success);

		if(!success)
		{
			glGetProgramInfoLog(id, 512, NULL, infoLog);
			log_error("Error in Linking Shaders\n%s\n", infoLog);
			exit(EXIT_FAILURE);
		}
	}
}

void compileShader(unsigned int* shader, const int shaderType, const char** shaderSource)
{
	*shader = glCreateShader(shaderType);
	glShaderSource(*shader, 1, shaderSource, NULL);
	glCompileShader(*shader);

	checkForErrors(*shader, GL_COMPILE_STATUS);
}

void initShaderProgram(unsigned int* shaderProgram, const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath)
{
	char* vertexShaderSource = readFile(vertexShaderSourcePath);
	char* fragmentShaderSource = readFile(fragmentShaderSourcePath);

	unsigned int vertexShader;
	compileShader(&vertexShader, GL_VERTEX_SHADER, (const char**)&vertexShaderSource);

	unsigned int fragmentShader;
	compileShader(&fragmentShader, GL_FRAGMENT_SHADER, (const char**)&fragmentShaderSource);

	*shaderProgram = glCreateProgram();
	glAttachShader(*shaderProgram, vertexShader);
	glAttachShader(*shaderProgram, fragmentShader);
	glLinkProgram(*shaderProgram);

	checkForErrors(*shaderProgram, GL_LINK_STATUS);

	free(vertexShaderSource);
	free(fragmentShaderSource);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void bindShaderProgram(unsigned int* shaderProgram)
{
	glUseProgram(*shaderProgram);
}

int getUniformLocation(unsigned int* shaderProgram, const char* uniformName)
{
	return glGetUniformLocation(*shaderProgram, uniformName);
}

void uploadInt(unsigned int* shaderProgram, const char* uniformName, int data)
{
	glUniform1i(getUniformLocation(shaderProgram, uniformName), data);
}

void uploadFloat(unsigned int* shaderProgram, const char* uniformName, float data)
{
	glUniform1f(getUniformLocation(shaderProgram, uniformName), data);
}

void uploadVec2(unsigned int* shaderProgram, const char* uniformName, vec2 data)
{
	glUniform2fv(getUniformLocation(shaderProgram, uniformName), 1, (float*)data);
}

void uploadVec3(unsigned int* shaderProgram, const char* uniformName, vec3 data)
{
	glUniform3fv(getUniformLocation(shaderProgram, uniformName), 1, (float*)data);
}

void uploadVec4(unsigned int* shaderProgram, const char* uniformName, vec4 data)
{
	glUniform4fv(getUniformLocation(shaderProgram, uniformName), 1, (float*)data);
}

void uploadMat4(unsigned int* shaderProgram, const char* uniformName, mat4 data)
{
	glUniformMatrix4fv(getUniformLocation(shaderProgram, uniformName), 1, GL_FALSE, (float*)data);
}

void destroyShaderProgram(unsigned int* shaderProgram)
{
	glDeleteProgram(*shaderProgram);
}
