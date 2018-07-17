/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:29:07 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/17 16:41:29 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static GLboolean	shader_load_src(const char *path, char *buffer)
{
	int		fd;

	if (!(fd = open(path, O_RDONLY)))
		return (GL_FALSE);
	read(fd, buffer, MAX_SOURCE_SIZE);
	close(fd);
	return (GL_TRUE);
}

GLboolean			shader_build_shader(GLint *shader, const GLenum shader_type,
												const char *shader_path)
{
	GLint			success;
	char			info_log[BUFFER_LOG];
	char			shader_src[MAX_SOURCE_SIZE];
	const GLchar	*shader_src_ptr;

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
		bzero(info_log, BUFFER_LOG);
		glGetShaderInfoLog(*shader, BUFFER_LOG, NULL, info_log);
		ft_dprintf(2, "[Error compilation shader :\n%s]\n", info_log);
		return (GL_FALSE);
	}
	return (GL_TRUE);
}

GLboolean			shader_build_shader_program(t_shader *shader,
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
		bzero(info_log, BUFFER_LOG);
		glGetShaderInfoLog(shader->program, BUFFER_LOG, NULL, info_log);
		ft_dprintf(2, "[Error compilation program :\n%s]\n", info_log);
		return (GL_FALSE);
	}
	return (GL_TRUE);
}
