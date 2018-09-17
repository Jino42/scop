#include "scop.h"

void			rbo_render(t_rbo *rbo, t_shader *shader, t_model *model, const float time)
{
	t_m_mesh	*m_mesh;

	m_mesh = model->m_mesh;

	glBindFramebuffer(GL_FRAMEBUFFER, rbo->framebuffer);
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
	glGenTextures(1, &rbo->texture_color_buffer);
	glBindTexture(GL_TEXTURE_2D, rbo->texture_color_buffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rbo->texture_color_buffer, 0);
	glGenRenderbuffers(1, &rbo->rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo->rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo->rbo); // now actually attach it
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
		glDeleteFramebuffers(1, &(*rbo)->framebuffer);
		glDeleteRenderbuffers(1, &(*rbo)->rbo);
		ft_memdel((void **)rbo);
	}
	return (NULL);
}
