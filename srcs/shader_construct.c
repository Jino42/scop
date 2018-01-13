/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_construct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 16:35:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/13 17:49:08 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static GLboolean	shader_load_src(const char *path, char *buffer)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (!fd)
		return (GL_FALSE);
	read(fd, buffer, MAX_SOURCE_SIZE);
	close(fd);
	return (GL_TRUE);
}

static GLboolean	shader_build_shader(GLint *shader, const GLenum shader_type,
												const char *shader_path)
{
	GLint			success;
	char			info_log[BUFFER_LOG];
	char			shader_src[MAX_SOURCE_SIZE];
	const GLchar	*shader_src_ptr;

	bzero(info_log, BUFFER_LOG);
	bzero(shader_src, MAX_SOURCE_SIZE);
	if (!shader_load_src(shader_path, shader_src))
	{
		ft_dprintf(2, "[Error load source shader of %s]\n", shader_path);
		return (GL_FALSE);
	}
	*shader = glCreateShader(shader_type);
	shader_src_ptr = shader_src;
	glShaderSource(*shader, 1, &shader_src_ptr, NULL);
	glCompileShader(*shader);
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetShaderInfoLog(*shader, BUFFER_LOG, NULL, info_log);
		ft_dprintf(2, "[Error compilation shader :\n%s]\n", info_log);
		return (GL_FALSE);
	}
	return (GL_TRUE);
}

static GLboolean	shader_build_shader_program(t_shader *shader,
										const GLint vertex_shader,
										const GLint fragment_shader)
{
	GLint	success;
	char	info_log[BUFFER_LOG];

	shader->program = glCreateProgram();
	glAttachShader(shader->program, vertex_shader);
	glAttachShader(shader->program, fragment_shader);
	glLinkProgram(shader->program);

	glGetProgramiv(shader->program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetShaderInfoLog(shader->program, BUFFER_LOG, NULL, info_log);
		ft_dprintf(2, "[Error compilation program :\n%s]\n", info_log);
		return (GL_FALSE);
	}
	return (GL_TRUE);
}

void			shader_use(t_shader *shader)
{
	glUseProgram(shader->program);
}

GLboolean		shader_construct(t_shader *shader,
									const char *vertex_shader_path,
									const char *fragment_shader_path)
{
	GLint	vertex_shader;
	GLint	fragment_shader;

	if (!shader_build_shader(&vertex_shader, GL_VERTEX_SHADER,
											vertex_shader_path))
		return (GL_FALSE);
	if (!shader_build_shader(&fragment_shader, GL_FRAGMENT_SHADER,
											fragment_shader_path))
		return (GL_FALSE);
	if (!shader_build_shader_program(shader, vertex_shader, fragment_shader))
		return (GL_FALSE);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	shader->use = &shader_use;
	return (true);
}
