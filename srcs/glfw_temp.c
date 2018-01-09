#include "scop.h"

void glfw_input(t_glfw *glfw)
{
    if(glfwGetKey(glfw->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfw->window, true);
}

void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
    glViewport(0, 0, width, height);
}
