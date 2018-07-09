#include "scop.h"

bool			loop(t_env *e)
{
	t_glfw		*glfw;

	glfw = e->glfw;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glPointSize(5.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while(!glfwWindowShouldClose(glfw->window))
	{
		fps_update(e->fps, &e->delta_time);
		glfw_update(e->glfw);
		cam_update(e->scene->cam, e->glfw, e->delta_time);
		printf("Cam: \n");
		printf("Position: %.2f %.2f %.2f\n", e->scene->cam->position.x,
										e->scene->cam->position.y,
										e->scene->cam->position.z);
		printf("Delta [%.3f]\n", e->delta_time);

		matrix_print(&e->scene->m_model->model[0]->transform, "matrix transform");
		matrix_print(&e->scene->cam->view, "matrix view");
		matrix_print(&e->scene->cam->projection, "matrix projection");
		/*
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
		if (glfwGetKey(glfw->window, GLFW_KEY_KP_ADD))
			matrix_scaling(&e->scene->m_model->model[0]->transform, 1.005f);
		if (glfwGetKey(glfw->window, GLFW_KEY_KP_SUBTRACT))
			matrix_scaling(&e->scene->m_model->model[0]->transform, 0.995f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (glfwGetKey(glfw->window, GLFW_KEY_I) == GLFW_PRESS)
			glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		scene_render(e->scene);
		glfwSwapBuffers(glfw->window);
		glfwPollEvents();
	}
	return (true);
}
