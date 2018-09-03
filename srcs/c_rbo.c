#include "scop.h"
/*
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
}*/

void			render_dynamique_texture(t_scene *scene, const float time)
{
	t_shader	*shader;
	t_model		*model;
	t_m_mesh	*m_mesh;

	shader = scene->m_shader_hidden->shader[SHADER_INDEX_DYNAMIQUE_TEXTURE];
	model = scene->m_model_hidden->model[MODEL_INDEX_PLAN];
	m_mesh = model->m_mesh;
	(void)time;
	glBindFramebuffer(GL_FRAMEBUFFER, scene->rbo->framebuffer);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	shader->use(shader);
	glUniform1f(glGetUniformLocation(shader->program, "time"), time);
	glBindVertexArray(m_mesh->mesh[0]->VAO);
	glDrawElements(GL_TRIANGLES, m_mesh->mesh[0]->nb_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

t_rbo		*rbo_construct(unsigned int width, unsigned int height)
{
	t_rbo *rbo;

	if (!(rbo = (t_rbo *)ft_memalloc(sizeof(t_rbo))))
		return (NULL);
	glGenFramebuffers(1, &rbo->framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, rbo->framebuffer);
	// create a color attachment texture
	glGenTextures(1, &rbo->texture_color_buffer);
	glBindTexture(GL_TEXTURE_2D, rbo->texture_color_buffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rbo->texture_color_buffer, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &rbo->rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo->rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo->rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		dprintf(2, "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return (rbo);
}

void		*rbo_destruct(t_rbo **rbo)
{
	if (rbo && *rbo)
	{
		ft_memdel((void **)rbo);
	}
	return (NULL);
}
