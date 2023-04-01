#pragma once

#include <cglm/cglm.h>

void initRay();
void drawRay(vec3 playerPos, float playerAngle, mat4 viewTimesProj);
void destroyRay();
