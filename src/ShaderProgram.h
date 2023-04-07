#pragma once

#include <cglm/cglm.h>

void initShaderProgram(unsigned int* shaderProgram, const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);
void bindShaderProgram(unsigned int* shaderProgram);

int getUniformLocation(unsigned int* shaderProgram, const char* uniformName);

void uploadInt(unsigned int* shaderProgram, const char* uniformName, int data);
void uploadFloat(unsigned int* shaderProgram, const char* uniformName, float data);
void uploadVec2(unsigned int* shaderProgram, const char* uniformName, vec2 data);
void uploadVec3(unsigned int* shaderProgram, const char* uniformName, vec3 data);
void uploadVec4(unsigned int* shaderProgram, const char* uniformName, vec4 data);
void uploadMat4(unsigned int* shaderProgram, const char* uniformName, mat4 data);

void destroyShaderProgram(unsigned int* shaderProgram);
