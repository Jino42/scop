#include "scop_glfw.h"
#include <strings.h>

void glfw_update(t_glfw *glfw)
{
    if(glfwGetKey(glfw->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfw->window, true);
}
