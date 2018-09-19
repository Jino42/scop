#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>
//#include <GL/glew.h>
#include "glad.c"
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	printf("%i %i %i\n", button, action, mods);
}

void error_callback(int e, const char *d)
{
	printf("Error %d: %s\n", e, d);
}

int main(void)
{
	GLFWwindow *win;

	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		dprintf(2, "[GFLW] failed to init!\n");
		exit(1);
	}
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL
	win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Demo", NULL, NULL);
	glfwMakeContextCurrent(win);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (0);
	sleep(7);
	glfwSetMouseButtonCallback(win, mouse_button_callback);

	while (1)
	{
		glfwPollEvents();
	}
}
