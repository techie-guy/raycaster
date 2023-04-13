#include "Application.h"

#include <glad/gl.h>
#include <cglm/struct.h>

#define UTILS_DEF
#include "Utils.h"

#include "Window.h"
#include "VertexAttributes.h"
#include "ShaderProgram.h"
#include "Map.h"
#include "Player.h"
#include "Raycaster.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512
#define WINDOW_TITLE "Raycaster"

Window window;
InputState inputState;

mat4 projectionMatrix;
mat4 viewMatrix;
mat4 viewTimesProj;

// Delta Time
float deltaTime = 0.0f;
float currentFrame = 0.0f;
float lastFrame = 0.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS)
	{
		if(key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) inputState.right = true;
		if(key == GLFW_KEY_LEFT || key == GLFW_KEY_A) inputState.left = true;
		if(key == GLFW_KEY_UP || key == GLFW_KEY_W) inputState.up = true;
		if(key == GLFW_KEY_DOWN || key == GLFW_KEY_S) inputState.down = true;
	}

	if(action == GLFW_RELEASE)
	{
		if(key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) inputState.right = false;
		if(key == GLFW_KEY_LEFT || key == GLFW_KEY_A) inputState.left = false;
		if(key == GLFW_KEY_UP || key == GLFW_KEY_W) inputState.up = false;
		if(key == GLFW_KEY_DOWN || key == GLFW_KEY_S) inputState.down = false;
	}
}

void init()
{
	window.width = WINDOW_WIDTH;
	window.height = WINDOW_HEIGHT;
	window.title = WINDOW_TITLE;

	initWindow(&window);
	setWindowKeyCallback(&window, key_callback);
	changeWindowColor("#333333", 1.0f);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	initMap();
	initPlayer();
	initRay();
}

void handleInput()
{
	handlePlayer(inputState, deltaTime);
}

void mainLoop()
{
	while(!shouldWindowClose(&window))
	{
		{
			currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
		}

		handleInput();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		{
			glm_mat4_identity(projectionMatrix);
			glm_mat4_identity(viewMatrix);

			glm_translate(viewMatrix, (vec3){0.0f, 0.0f, -1.0f});
			glm_ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, 0.001f, 1000.0f, projectionMatrix);

			glm_mat4_mulN((mat4* []){&projectionMatrix, &viewMatrix}, 2, viewTimesProj);
		}

		drawMap(viewTimesProj);
		drawPlayer(viewTimesProj);
		drawRay(playerPos, playerAngle, viewTimesProj);

		updateWindow(&window);
	}

}

void cleanup()
{
	destroyRay();
	destroyMap();
	destroyPlayer();

	destroyWindow(&window);
}

void runApplication()
{
	init();
	mainLoop();
	cleanup();
}
