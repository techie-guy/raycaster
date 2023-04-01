#include "Player.h"
#include "VertexAttributes.h"
#include "ShaderProgram.h"
#include <glad/gl.h>

VertexAttributes playerVertexAttributes;
unsigned int playerShaderProgram;

vec3 playerDeltaPos = {0.0f, 0.0f};

vec3 playerPos = {64.0f*3, 64.0f*2, 0.0f};
float playerAngle = 0.0f;
float playerAngleSpeed = 2.0f;
float playerSpeed = 2.0f;

Vertex playerVertices[1] =
{
	{{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f}},
};

unsigned int playerIndices[1] =
{
	0
};

void initPlayer()
{
	playerDeltaPos[0] = cos(playerAngle) * playerSpeed;
	playerDeltaPos[1] = sin(playerAngle) * playerSpeed;

	initShaderProgram(&playerShaderProgram, "assets/shaders/player-vertex-shader.glsl", "assets/shaders/player-fragment-shader.glsl");
	initVertexAttributes(&playerVertexAttributes, NULL, sizeof(playerVertices), playerIndices, sizeof(playerIndices));
}

void handlePlayer(InputState inputState, float deltaTime)
{
	if(inputState.right)
	{
		playerAngle += playerAngleSpeed * deltaTime;
		if(playerAngle > glm_rad(360)) playerAngle -= glm_rad(360);

		playerDeltaPos[0] = cos(playerAngle) * playerSpeed;
		playerDeltaPos[1] = sin(playerAngle) * playerSpeed;
	}
	if(inputState.left)
	{
		playerAngle -= playerAngleSpeed * deltaTime;
		if(playerAngle < 0) playerAngle += glm_rad(360);

		playerDeltaPos[0] = cos(playerAngle) * playerSpeed;
		playerDeltaPos[1] = sin(playerAngle) * playerSpeed;
	}

	if(inputState.up)
	{
		glm_vec3_add(playerPos, playerDeltaPos, playerPos);
	}
	if(inputState.down)
	{
		glm_vec3_sub(playerPos, playerDeltaPos, playerPos);
	}
}

void drawPlayer(mat4 viewTimesProj)
{
	glPointSize(20.0f);

	bindShaderProgram(&playerShaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(playerShaderProgram, "viewTimesProj"), 1, GL_FALSE, (float*)viewTimesProj);

	playerVertices[0].position[0] = playerPos[0];
	playerVertices[0].position[1] = playerPos[1];

	bindVAO(&playerVertexAttributes);
	bindVBO(&playerVertexAttributes);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(playerVertices), playerVertices);
	glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, 0);
}

void destroyPlayer()
{
	destroyShaderProgram(&playerShaderProgram);
	destroyVertexAttributes(&playerVertexAttributes);
}
