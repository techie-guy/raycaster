#pragma once

#include "Utils.h"

extern vec3 playerPos;
extern float playerAngle;
extern float playerAngleSpeed;
extern float playerSpeed;

void initPlayer();
void handlePlayer(InputState inputState, float deltaTime);
void drawPlayer(mat4 viewTimesProj);
void destroyPlayer();
