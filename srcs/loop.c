#include "scop.h"
#include "scop_nk.h"

bool			loop(t_env *e)
{
	t_nk *nk;

	if (!(nk = nk_construct(e->glfw->window)))
		return (false);

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

		nk_update(nk);
		nk_scene(nk, e->scene);
		cam_update(e->scene->cam, e->glfw, e->delta_time);
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
		if (glfwGetKey(glfw->window, GLFW_KEY_U))
			scene_write(e->scene, "./la.json");
		if (glfwGetKey(glfw->window, GLFW_KEY_KP_ADD))
			matrix_scaling(&e->scene->m_model->model[0]->transform, 1.005f);
		if (glfwGetKey(glfw->window, GLFW_KEY_KP_SUBTRACT))
			matrix_scaling(&e->scene->m_model->model[0]->transform, 0.995f);
		if (glfwGetKey(glfw->window, GLFW_KEY_KP_DIVIDE))
		{
			matrixgl_translation(&e->scene->m_model->model[0]->transform, &e->scene->m_model->model[0]->negative_center);
			matrixgl_rotation_x(&e->scene->m_model->model[0]->transform, 0.01f);
			matrixgl_translation(&e->scene->m_model->model[0]->transform, &e->scene->m_model->model[0]->center);
		}

		t_vector move;
		move = vector_construct(0.0f, 0.0f, 0.1f);
		if (glfwGetKey(glfw->window, GLFW_KEY_I))
		{
			vector_add(&e->scene->m_model->model[0]->center, &move);
			vector_sub(&e->scene->m_model->model[0]->negative_center, &move);
			matrixgl_translation(&e->scene->m_model->model[0]->transform, &move);
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (glfwGetKey(glfw->window, GLFW_KEY_I) == GLFW_PRESS)
			glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glPointSize(5.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		scene_render(e->scene);
		nk_render(nk);
		glfwSwapBuffers(glfw->window);
		glfwPollEvents();
	}
	return (true);
}
