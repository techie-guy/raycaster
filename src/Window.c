#include <glad/gl.h>

#include "Window.h"
#include "Utils.h"

void initWindow(Window* window)
{
	glfwInit();

	window->handle = glfwCreateWindow(window->width, window->height, window->title, NULL, NULL);
	if(!window->handle)
	{
		glfwTerminate();
		log_error("Failed to Initialize GLFW Window!\n");
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window->handle);
	glfwSwapInterval(1);

	gladLoadGL(glfwGetProcAddress);
}

void updateWindow(Window* window)
{
	glfwSwapBuffers(window->handle);
	glfwPollEvents();
}

int shouldWindowClose(Window* window)
{
	return glfwWindowShouldClose(window->handle);
}

void changeWindowColor(char colorCode[7], float alpha)
{
	char hexString[9] = {};

	hexString[0] = '0';
	hexString[1] = 'x';
	hexString[8] = '\0';

	for(size_t i = 0; i < 6; i++)
	{
		hexString[i+2] = colorCode[i+1];
	}

	int hexCode = strtol(hexString, NULL, 16);

	glClearColor(((hexCode >> 16) & 0xFF)/255.0f, ((hexCode >> 8) & 0xFF)/255.0f, ((hexCode) & 0xFF)/255.0f, alpha);
}

void setWindowKeyCallback(Window* window, GLFWkeyfun callback)
{
	glfwSetKeyCallback(window->handle, callback);
}

void destroyWindow(Window* window)
{
	glfwDestroyWindow(window->handle);
	glfwTerminate();
}
