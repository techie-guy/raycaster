#include "Map.h"
#include "ShaderProgram.h"
#include "Utils.h"
#include <glad/gl.h>

typedef struct
{
	Vertex vertices[4];
} Square;

static VertexAttributes mapVertexAttributes;
static unsigned int mapShaderprogram;

static Square mapVertices[MAP_SIZE];
static unsigned int mapIndices[MAP_SIZE*6];

void initMap()
{
	// Filling up the Vertices and Indices
	for(int y = 0; y < MAP_SIZE_Y; y++)
	{
		for(int x = 0; x < MAP_SIZE_X; x++)
		{
			int index = (MAP_SIZE_Y - y - 1) * MAP_SIZE_X + x;
			int xOffset = x * MAP_SIZE;
			int yOffset = y * MAP_SIZE;

			vec4 color;
			memcpy(color, mapEmptyCellColor, sizeof(vec4));

			if(map[index] == 1)
			{
				memcpy(color, mapWallColor, sizeof(vec4));
			}

			Square square = {
				(Vertex){{xOffset + 1, yOffset + 1, 0.0f}, {color[0], color[1], color[2], color[3]}, {0.0f, 0.0f}},
				(Vertex){{xOffset + 1, yOffset + MAP_GRID_CELL_SIZE - 1, 0.0f}, {color[0], color[1], color[2], color[3]}, {0.0f, 0.0f}},
				(Vertex){{xOffset + MAP_GRID_CELL_SIZE - 1, yOffset + MAP_GRID_CELL_SIZE - 1, 0.0f}, {color[0], color[1], color[2], color[3]}, {0.0f, 0.0f}},
				(Vertex){{xOffset + MAP_GRID_CELL_SIZE - 1, yOffset + 1, 0.0f}, {color[0], color[1], color[2], color[3]}, {0.0f, 0.0f}},
			};

			mapVertices[index] = square;
		}
	}

	for(size_t i = 0; i < MAP_SIZE * 6; i += 6)
	{
		static int offset = 0;

		mapIndices[i + 0] = 0 + offset;
		mapIndices[i + 1] = 1 + offset;
		mapIndices[i + 2] = 3 + offset;

		mapIndices[i + 3] = 1 + offset;
		mapIndices[i + 4] = 2 + offset;
		mapIndices[i + 5] = 3 + offset;

		offset += 4;
	}

	initShaderProgram(&mapShaderprogram, "assets/shaders/map-vertex-shader.glsl", "assets/shaders/map-fragment-shader.glsl");
	initVertexAttributes(&mapVertexAttributes, mapVertices, sizeof(mapVertices), mapIndices, sizeof(mapIndices));
}

void drawMap(mat4 viewTimesProj)
{
	bindShaderProgram(&mapShaderprogram);
	uploadMat4(&mapShaderprogram, "viewTimesProj", viewTimesProj);

	bindVAO(&mapVertexAttributes);
	glDrawElements(GL_TRIANGLES, sizeof(mapIndices)/sizeof(mapIndices[0]), GL_UNSIGNED_INT, 0);
}

void destroyMap()
{
	destroyShaderProgram(&mapShaderprogram);
	destroyVertexAttributes(&mapVertexAttributes);
}
