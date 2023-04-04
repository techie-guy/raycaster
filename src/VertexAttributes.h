#pragma once

#include <cglm/cglm.h>

typedef struct
{
	vec3 position;
	vec4 color;
	vec2 texCoord;
} Vertex;

typedef struct
{
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
} VertexAttributes;


void initVertexAttributes(VertexAttributes* attrib, void* vertexData, size_t vertexDataSize, void* indexData, size_t indexDataSize);
void bindVAO(VertexAttributes* attrib);
void bindVBO(VertexAttributes* attrib);
void bindEBO(VertexAttributes* attrib);
void destroyVertexAttributes(VertexAttributes* attrib);
