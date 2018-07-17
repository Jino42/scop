/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:26:38 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/17 16:36:52 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			shader_use(t_shader *shader)
{
	glUseProgram(shader->program);
}

void			*shader_destruct(t_shader **shader)
{
	if (shader && *shader)
	{
		glDeleteProgram((*shader)->program);
		ft_memdel((void **)&(*shader)->name);
		ft_memdel((void **)&(*shader)->path_vertex);
		ft_memdel((void **)&(*shader)->path_fragment);
		ft_memdel((void **)shader);
	}
	return (NULL);
}

static bool		shader_construct_build(t_shader *shader,
										const char *vertex_shader_path,
										const char *fragment_shader_path)
{
	GLint		fragment_shader;
	GLint		vertex_shader;

	fragment_shader = 0;
	vertex_shader = 0;
	if (!shader_build_shader(&vertex_shader, GL_VERTEX_SHADER,
											vertex_shader_path)
		|| !shader_build_shader(&fragment_shader, GL_FRAGMENT_SHADER,
												fragment_shader_path)
		|| !shader_build_shader_program(shader, vertex_shader, fragment_shader))
	{
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		return (false);
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	return (true);
}

t_shader		*shader_construct(const char *vertex_shader_path,
									const char *fragment_shader_path,
									const char *name)
{
	t_shader	*shader;

	if (!(shader = ft_memalloc(sizeof(t_shader))))
		return (NULL);
	if (!(shader_construct_build(shader, vertex_shader_path,
				fragment_shader_path)))
		return (shader_destruct(&shader));
	shader->use = &shader_use;
	shader->name = strdup(name);
	shader->path_vertex = strdup(vertex_shader_path);
	shader->path_fragment = strdup(fragment_shader_path);
	return (shader);
}
