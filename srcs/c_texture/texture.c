/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 19:01:38 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 21:31:21 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** https://fr.wikipedia.org/wiki/Truevision_Targa
*/

#include "scop.h"

t_texture		*texture_construct(const char *path, const int type)
{
	t_texture		*texture;

	if (!(texture = ft_memalloc(sizeof(t_texture))))
		return (NULL);
	texture->name = strdup(path);
	texture->flag |= type;
	if (!texture_load_tga(texture, path))
		return (texture_destruct(&texture));
	texture->name = strdup(path);
	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
								texture->width,
								texture->height,
								0, GL_BGRA, GL_UNSIGNED_BYTE,
								texture->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	ft_memdel((void *)&texture->data);
	return (texture);
}

void			*texture_destruct(t_texture **texture)
{
	if (texture && *texture)
	{
		if ((*texture)->data)
		{
			ft_memdel((void **)&(*texture)->data);
			glDeleteTextures(1, &(*texture)->id);
		}
		ft_memdel((void **)(&(*texture)->name));
		ft_memdel((void **)texture);
	}
	return (NULL);
}
