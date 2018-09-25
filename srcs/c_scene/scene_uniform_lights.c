/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_uniform_lights.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:53:48 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 20:06:50 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	scene_set_uniform_lights_basique(t_light *light,
												t_shader *shader,
												unsigned int i)
{
	char			buffer[255];

	sprintf(buffer, "u_light[%i].ambient", i);
	glUniform3fv(glGetUniformLocation(shader->program, buffer), 1,
		(GLfloat *)&light->ambient);
	sprintf(buffer, "u_light[%i].diffuse", i);
	glUniform3fv(glGetUniformLocation(shader->program, buffer), 1,
		(GLfloat *)&light->diffuse);
	sprintf(buffer, "u_light[%i].specular", i);
	glUniform3fv(glGetUniformLocation(shader->program, buffer), 1,
		(GLfloat *)&light->specular);
	sprintf(buffer, "u_light[%i].position", i);
	glUniform3fv(glGetUniformLocation(shader->program, buffer), 1,
		(GLfloat *)&light->position);
	sprintf(buffer, "u_light[%i].direction", i);
	glUniform3fv(glGetUniformLocation(shader->program, buffer), 1,
		(GLfloat *)&light->direction);
	sprintf(buffer, "u_light[%i].intensity", i);
	glUniform1f(glGetUniformLocation(shader->program, buffer),
		light->intensity);
}

static void	scene_set_uniform_lights_complex(t_light *light,
												t_shader *shader,
												unsigned int i)
{
	char			buffer[255];

	sprintf(buffer, "u_light[%i].constent", i);
	glUniform1f(glGetUniformLocation(shader->program, buffer),
		light->constent);
	sprintf(buffer, "u_light[%i].linear", i);
	glUniform1f(glGetUniformLocation(shader->program, buffer),
		light->linear);
	sprintf(buffer, "u_light[%i].quadratic", i);
	glUniform1f(glGetUniformLocation(shader->program, buffer),
		light->quadratic);
	sprintf(buffer, "u_light[%i].spot_little_radius", i);
	glUniform1f(glGetUniformLocation(shader->program, buffer),
		light->spot_little_radius);
	sprintf(buffer, "u_light[%i].spot_big_radius", i);
	glUniform1f(glGetUniformLocation(shader->program, buffer),
		light->spot_big_radius);
	sprintf(buffer, "u_light[%i].type", i);
	glUniform1i(glGetUniformLocation(shader->program, buffer),
		light->flag & 0xFF);
}

void		scene_set_uniform_lights(t_m_light *m_light, t_shader *shader)
{
	unsigned int	i;

	i = 0;
	while (i < m_light->size)
	{
		scene_set_uniform_lights_basique(m_light->light[i], shader, i);
		scene_set_uniform_lights_complex(m_light->light[i], shader, i);
		i++;
	}
}
