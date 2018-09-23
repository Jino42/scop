#include "scop.h"
#include "scop_nk.h"

bool			loop(t_env *e)
{
	t_glfw		*glfw;

	glfw = e->glfw;

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
			glfw_destruct(&glfw);
			return (false);
		}
		cam_update(e->scene->cam, e->glfw, e->delta_time);
		rbo_render(e->scene->rbo,
					e->scene->m_shader_hidden->shader[SHADER_INDEX_DYNAMIQUE_TEXTURE],
					e->scene->m_model_hidden->model[MODEL_INDEX_PLAN],
					e->fps->time);

		scene_render(e->scene, e->fps->time, fps_timestamp(e->fps));
		nk_render(glfw->nk);

		glfwSwapBuffers(glfw->window);
		glfwPollEvents();

	}
	return (true);
}
