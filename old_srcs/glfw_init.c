#include "scop.h"

bool		glfw_init(t_glfw *glfw)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfw->window = glfwCreateWindow(WIDTH, HEIGHT, "scop", NULL, NULL);
	if (glfw->window == NULL)
		return (false);
	glfwMakeContextCurrent(glfw->window);
	glfwSetFramebufferSizeCallback(glfw->window, &glfw_framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (false);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glfwSwapInterval(0);
	return (true);
}
