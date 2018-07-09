#include "scop.h"
#include <stdlib.h>
#include <strings.h>

t_glfw		*glfw_construct(char *name, int width, int height)
{
	t_glfw	*glfw;

	if (!(glfw = malloc(sizeof(t_glfw))))
		return (NULL);
	bzero(glfw, sizeof(t_glfw));
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfw->window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (glfw->window == NULL)
		return (glfw_destruct(&glfw));
	glfwMakeContextCurrent(glfw->window);
	glfwSetFramebufferSizeCallback(glfw->window, &glfw_callback_resize);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (glfw_destruct(&glfw));
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glfwSwapInterval(0);
	glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(glfw->window, &event_mouse);
	return (glfw);
}
