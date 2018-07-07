#include "scop_glfw.h"
#include <stdlib.h>

void			*glfw_destruct(t_glfw **glfw)
{
	glfwTerminate();
	if (glfw && *glfw)
	{
		free(*glfw);
		*glfw = NULL;
	}
	return (NULL);
}
