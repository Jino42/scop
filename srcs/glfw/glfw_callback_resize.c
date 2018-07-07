#include "scop_glfw.h"

void glfw_callback_resize(GLFWwindow* window, int width, int height)
{
	(void)window;
    glViewport(0, 0, width, height);
}
