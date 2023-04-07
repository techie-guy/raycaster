#include "Raycaster.h"
#include "VertexAttributes.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Map.h"
#include "Utils.h"
#include <glad/gl.h>

Vertex sceneLineVertices[4];

unsigned int sceneLineIndices[6] =
{
	0, 1, 2,
	2, 3, 0
};

Vertex lineVertices[2];
unsigned int lineIndices[2] =
{
	0, 1
};

VertexAttributes rayVertexAttributes;
unsigned int rayShaderProgram;

VertexAttributes sceneVertexAttributes;
unsigned int sceneShaderProgram;
Texture texture;

void initRay()
{
	initShaderProgram(&rayShaderProgram, "assets/shaders/line-vertex-shader.glsl", "assets/shaders/line-fragment-shader.glsl");
	initVertexAttributes(&rayVertexAttributes, NULL, sizeof(lineVertices), lineIndices, sizeof(lineIndices));

	initShaderProgram(&sceneShaderProgram, "assets/shaders/line-vertex-shader.glsl", "assets/shaders/line-fragment-shader.glsl");
	initVertexAttributes(&sceneVertexAttributes, NULL, sizeof(sceneLineVertices), sceneLineIndices, sizeof(sceneLineIndices));
	initTexture(&texture, "assets/textures/image.png");
}

void drawRay(vec3 playerPos, float playerAngle, mat4 viewTimesProj)
{
	const int maxRayCount = 60, rayAngleOffset = 30, maxDOF = MAP_SIZE_X;
	float finalDist;

	int mapX, mapY, mapPosition;
	int dof;
	vec3 rayPos;
	float rayAngle, xOffset, yOffset;

	rayAngle = playerAngle - glm_rad(rayAngleOffset);
	if(rayAngle < 0)
	{
		rayAngle += glm_rad(360);
	}
	if(rayAngle > glm_rad(360))
	{
		rayAngle -= glm_rad(360);
	}

	for(int rayCount = 0; rayCount < maxRayCount; rayCount++)
	{
		// Check for Horizontal Hit
		dof = 0;
		float horizontalDist = 100000;
		vec3 horizontalPos = {playerPos[0], playerPos[1]};
		float aTan = -1/tan(rayAngle);

		if(rayAngle > glm_rad(180)) // Looking Down
		{
			rayPos[1] = (((int)playerPos[1] >> 6) << 6) - 0.0001;
			rayPos[0] = (playerPos[1] - rayPos[1]) * aTan + playerPos[0];

			yOffset = -MAP_GRID_CELL_SIZE;
			xOffset = -yOffset * aTan;
		}

		if(rayAngle < glm_rad(180)) // Looking Up
		{
			rayPos[1] = (((int)playerPos[1] >> 6) << 6) + MAP_GRID_CELL_SIZE;
			rayPos[0] = (playerPos[1] - rayPos[1]) * aTan + playerPos[0];

			yOffset = MAP_GRID_CELL_SIZE;
			xOffset = -yOffset * aTan;
		}

		if(rayAngle == 0 || rayAngle == glm_rad(180)) // Looking Straight Left or Right
		{
			rayPos[0] = playerPos[0];
			rayPos[1] = playerPos[1];

			dof = maxDOF;
		}

		while(dof < maxDOF)
		{
			mapX = (int)rayPos[0] >> 6;
			mapY = (int)rayPos[1] >> 6;

			mapPosition = (MAP_SIZE_Y - mapY - 1) * MAP_SIZE_X + mapX;
			if(mapPosition > 0 && mapPosition < MAP_SIZE && map[mapPosition] == 1) // Hit The Wall
			{
				horizontalPos[0] = rayPos[0];
				horizontalPos[1] = rayPos[1];
				horizontalDist = glm_vec3_distance(playerPos, horizontalPos);

				dof = maxDOF;
			}
			else
			{
				rayPos[0] += xOffset;
				rayPos[1] += yOffset;

				dof++;
			}
		}

		// Check for Vertical Hit
		dof = 0;
		float verticalDist = 100000;
		vec3 verticalPos = {playerPos[0], playerPos[1]};
		float nTan = -tan(rayAngle);

		if(rayAngle > glm_rad(90) && rayAngle < glm_rad(270)) // Looking Left
		{
			rayPos[0] = (((int)playerPos[0] >> 6) << 6) - 0.0001;
			rayPos[1] = (playerPos[0] - rayPos[0]) * nTan + playerPos[1];

			xOffset = -MAP_GRID_CELL_SIZE;
			yOffset = -xOffset * nTan;
		}

		if(rayAngle < glm_rad(90) || rayAngle > glm_rad(270)) // Looking Right
		{
			rayPos[0] = (((int)playerPos[0] >> 6) << 6) + MAP_GRID_CELL_SIZE;
			rayPos[1] = (playerPos[0] - rayPos[0]) * nTan + playerPos[1];

			xOffset = MAP_GRID_CELL_SIZE;
			yOffset = -xOffset * nTan;
		}

		if(rayAngle == 0 || rayAngle == glm_rad(180)) // Looking Straight Up or Down
		{
			rayPos[0] = playerPos[0];
			rayPos[1] = playerPos[1];

			dof = maxDOF;
		}

		while(dof < maxDOF)
		{
			mapX = (int)rayPos[0] >> 6;
			mapY = (int)rayPos[1] >> 6;

			mapPosition = (MAP_SIZE_Y - mapY - 1) * MAP_SIZE_X + mapX;
			if(mapPosition > 0 && mapPosition < MAP_SIZE && map[mapPosition] == 1) // Hit The Wall
			{
				verticalPos[0] = rayPos[0];
				verticalPos[1] = rayPos[1];
				verticalDist = glm_vec3_distance(playerPos, verticalPos);

				dof = maxDOF;
			}
			else
			{
				rayPos[0] += xOffset;
				rayPos[1] += yOffset;

				dof++;
			}
		}

		vec4 sceneLighting; // For Shading/Lighting

		if(verticalDist < horizontalDist)
		{
			rayPos[0] = verticalPos[0];
			rayPos[1] = verticalPos[1];

			finalDist = verticalDist;

			memcpy(sceneLighting, (vec4){0.9f, 0.0f, 0.0f, 1.0f}, sizeof(vec4));
		}

		if(horizontalDist < verticalDist)
		{
			rayPos[0] = horizontalPos[0];
			rayPos[1] = horizontalPos[1];

			finalDist = horizontalDist;

			memcpy(sceneLighting, (vec4){0.7f, 0.0f, 0.0f, 1.0f}, sizeof(vec4));
		}

		// Draw The Ray
//		lineVertices[0] = (Vertex){{playerPos[0], playerPos[1], 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}};
//		lineVertices[1] = (Vertex){{rayPos[0], rayPos[1], 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}};

//		bindShaderProgram(&rayShaderProgram);

//		glUniformMatrix4fv(glGetUniformLocation(rayShaderProgram, "viewTimesProj"), 1, GL_FALSE, (float*)viewTimesProj);

//		bindVAO(&rayVertexAttributes);
//		bindVBO(&rayVertexAttributes);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(lineVertices), lineVertices);
//		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);


		// "3D" Scene
		float cosAngle = playerAngle - rayAngle;
		if(cosAngle < 0)
		{
			cosAngle += glm_rad(360);
		}
		if(cosAngle > glm_rad(360))
		{
			cosAngle -= glm_rad(360);
		}

		finalDist = finalDist * cos(cosAngle);

		float width = 320;
		float height = 160;
		float lineWidth = 8;

		float lineHeight = (MAP_SIZE * width)/finalDist;
		if(lineHeight > width)
			lineHeight = width;

		float lineOffset = height - lineHeight/2;

		sceneLineVertices[0] = (Vertex){{rayCount * lineWidth + 530, lineOffset, 0.0f}, {sceneLighting[0], sceneLighting[1], sceneLighting[2], sceneLighting[3]}, {0.0f, 0.0f}};
		sceneLineVertices[1] = (Vertex){{rayCount * lineWidth + 530 + lineWidth, lineOffset, 0.0f}, {sceneLighting[0], sceneLighting[1], sceneLighting[2], sceneLighting[3]}, {0.0f, 1.0f}};
		sceneLineVertices[2] = (Vertex){{rayCount * lineWidth + 530 + lineWidth, lineOffset + lineHeight, 0.0f}, {sceneLighting[0], sceneLighting[1], sceneLighting[2], sceneLighting[3]}, {1.0f, 1.0f}};
		sceneLineVertices[3] = (Vertex){{rayCount * lineWidth + 530, lineOffset + lineHeight, 0.0f}, {sceneLighting[0], sceneLighting[1], sceneLighting[2], sceneLighting[3]}, {1.0f, 0.0f}};

		bindShaderProgram(&sceneShaderProgram);
		bindTexture(&texture);
		uploadMat4(&rayShaderProgram, "viewTimesProj", viewTimesProj);

		bindVAO(&sceneVertexAttributes);
		bindVBO(&sceneVertexAttributes);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(sceneLineVertices), sceneLineVertices);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		rayAngle += glm_rad(1);
		if(rayAngle < 0)
		{
			rayAngle += glm_rad(360);
		}
		if(rayAngle > glm_rad(360))
		{
			rayAngle -= glm_rad(360);
		}
	}
}

void destroyRay()
{
	destroyTexture(&texture);
	
	destroyShaderProgram(&rayShaderProgram);
	destroyVertexAttributes(&rayVertexAttributes);

	destroyShaderProgram(&sceneShaderProgram);
	destroyVertexAttributes(&sceneVertexAttributes);
}
