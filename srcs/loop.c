#include "scop.h"
#include "scop_nk.h"


void m_model_update(t_m_model *m_model)
{
	t_model *model;
	size_t	i;

	i = 0;
	while (i < m_model->size)
	{
		model = m_model->model[i];
		if (model->flag & MODEL_ROTATE)
		{
			model->update = true;
			model->rotation.y += 0.01f;
		}
		i++;
	}
}

bool			loop(t_env *e)
{
	t_glfw		*glfw;

	glfw = e->glfw;
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glPointSize(5.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m_model_setup(e->scene->m_model);
	while(!glfwWindowShouldClose(glfw->window))
	{
		fps_update(e->fps, &e->delta_time);
		e->scene->timestamp = fps_timestamp(e->fps);
		glfw_update(e->glfw);
		m_model_update(e->scene->m_model);
		nk_update(glfw->nk);
		if (!(nk_scene(glfw->nk, &e->scene)))
		{
			nk_destruct(&glfw->nk);
			return (false);
		}
		cam_update(e->scene->cam, e->glfw, e->delta_time);
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
		if (glfwGetKey(glfw->window, GLFW_KEY_I) == GLFW_PRESS)
			glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		rbo_render(e->scene->rbo,
					e->scene->m_shader_hidden->shader[SHADER_INDEX_DYNAMIQUE_TEXTURE],
					e->scene->m_model_hidden->model[MODEL_INDEX_PLAN],
					e->fps->time);


		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable (GL_STENCIL_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		glPointSize(5.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glStencilMask (0xFF);
		glDepthFunc (GL_LESS);

		scene_render(e->scene, e->fps->time, fps_timestamp(e->fps));
		nk_render(glfw->nk);

		glfwSwapBuffers(glfw->window);
		glfwPollEvents();

	}
	return (true);
}
