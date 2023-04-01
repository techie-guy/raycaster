#pragma once

void initShaderProgram(unsigned int* shaderProgram, const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);
void bindShaderProgram(unsigned int* shaderProgram);
void destroyShaderProgram(unsigned int* shaderProgram);
