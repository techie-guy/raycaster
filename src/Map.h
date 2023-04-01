#pragma once

#include "VertexAttributes.h"

#define MAP_SIZE_X 8
#define MAP_SIZE_Y 8
#define MAP_GRID_CELL_SIZE 64
#define MAP_SIZE MAP_SIZE_X * MAP_SIZE_Y

static int map[MAP_SIZE] =
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

static vec4 mapEmptyCellColor = {0.0f, 0.0f, 0.0f, 1.0f};
static vec4 mapWallColor = {1.0f, 1.0f, 1.0f, 1.0f};

void initMap();
void drawMap(mat4 viewTimesProj);
void destroyMap();
