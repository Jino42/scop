#include "scop.h"
#include "scop_nk.h"

void			init_render_dynamique_texture(t_scene *scene)
{
	printf("INITIALISED\n");
	glGenFramebuffers(1, &scene->framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, scene->framebuffer);
	// create a color attachment texture
	glGenTextures(1, &scene->texture_color_buffer);
	glBindTexture(GL_TEXTURE_2D, scene->texture_color_buffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, scene->texture_color_buffer, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &scene->rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, scene->rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, scene->rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
 		dprintf(2, "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void			render_dynamique_texture(t_scene *scene, const float time)
{
	t_shader	*shader;
	t_model		*model;
	t_m_mesh	*m_mesh;

	shader = scene->m_shader_hidden->shader[SHADER_INDEX_DYNAMIQUE_TEXTURE];
	model = scene->m_model_hidden->model[MODEL_INDEX_PLAN];
	m_mesh = model->m_mesh;
	(void)time;
	glBindFramebuffer(GL_FRAMEBUFFER, scene->framebuffer);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	shader->use(shader);
	glUniform1f(glGetUniformLocation(shader->program, "time"), time);
	glBindVertexArray(m_mesh->mesh[0]->VAO);
	glDrawElements(GL_TRIANGLES, m_mesh->mesh[0]->nb_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	/*glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	screenShader.use();
	glBindVertexArray(quadVAO);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, scene->texture_color_buffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);*/
}

bool			loop(t_env *e)
{
	init_render_dynamique_texture(e->scene);
	t_nk *nk;

	if (!(nk = nk_construct(e->glfw->window)))
		return (false);

	t_glfw		*glfw;

	glfw = e->glfw;
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glPointSize(5.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while(!glfwWindowShouldClose(glfw->window))
	{
		fps_update(e->fps, &e->delta_time);
		glfw_update(e->glfw);

		nk_update(nk);
		if (!(nk_scene(nk, &e->scene)))
		{
			nk_destruct(&nk);
			return (false);
		}
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
		if (glfwGetKey(glfw->window, GLFW_KEY_I) == GLFW_PRESS)
			glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		render_dynamique_texture(e->scene, e->fps->time);


		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable (GL_STENCIL_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		glPointSize(5.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// glDepthMask (GL_FALSE); Lecture seulement du test de profondeur + Elimination des fragment shader a la mano
		glStencilMask (0xFF);
		glDepthFunc (GL_LESS);

		scene_render(e->scene, e->fps->time);


		render_dynamique_texture(e->scene, e->fps->time);
		nk_render(nk);

		glfwSwapBuffers(glfw->window);
		glfwPollEvents();

	}
	nk_destruct(&nk);
	return (true);
}
