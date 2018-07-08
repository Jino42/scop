#include "scop.h"

bool			loop(t_env *e)
{
	t_glfw		*glfw;
	t_matrix	view;

	glfw = e->glfw;
	while(!glfwWindowShouldClose(glfw->window))
	{
		/*
		update_fps(&e->fps);
		glfw_input(glfw);
		event_cam(e, &e->cam, &e->glfw);

		if (glfwGetKey(glfw->window, GLFW_KEY_F) == GLFW_PRESS)
		{
			(model->type_draw == GL_FILL) ? (model->type_draw = GL_LINE) : (model->type_draw = GL_FILL);
			glPolygonMode(GL_FRONT_AND_BACK, model->type_draw);
		}
		if (glfwGetKey(glfw->window, GLFW_KEY_KP_ADD))
			matrix_scaling(&model->transform, 1.005f);
		if (glfwGetKey(glfw->window, GLFW_KEY_KP_SUBTRACT))
			matrix_scaling(&model->transform, 0.995f);
		*/

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (glfwGetKey(glfw->window, GLFW_KEY_I) == GLFW_PRESS)
			glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		view = matrixgl_view(e->cam);

		//model_render(model, &e->cam, light, &view, &projection, shader);
		//model_render(obj_light, &e->cam, light, &view, &projection, shader_l);

		glfwSwapBuffers(glfw->window);
		glfwPollEvents();
	}
	return (true);
}
