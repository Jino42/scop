/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_uniform_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:54:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/10/16 16:56:00 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		scene_set_uniform_texture_personnal(t_shader *shader,
												t_material *material_personnal)
{
	if (material_personnal->flag & MATERIAL_MAP_DIFFUSE)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, material_personnal->texture_diffuse);
		glUniform1i(glGetUniformLocation(shader->program,
			"u_texture_personnal"), 1);
		glUniform1i(glGetUniformLocation(shader->program,
			"u_material_personnal.texture_diffuse"), 1);
	}
	else
	{
		glUniform1i(glGetUniformLocation(shader->program,
			"u_material_personnal.texture_diffuse"), 0);
	}
}

void		scene_set_uniform_texture_basic(t_shader *shader,
												t_model *model,
												t_material *material)
{
	if (model->flag & MODEL_USE_TEXTURE
		&& material->flag & MATERIAL_MAP_DIFFUSE)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, material->texture_diffuse);
		glUniform1i(glGetUniformLocation(shader->program, "u_texture"), 2);
	}
}
