/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 22:16:06 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/21 21:03:25 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static bool	size_texture(t_texture *texture, const int fd, uint32_t *size_tex)
{
	read(fd, &texture->width, sizeof(uint32_t));
	read(fd, &texture->height, sizeof(uint32_t));
	*size_tex = texture->width * texture->height * 4;
	if (texture->width > 4996 || texture->height > 4996)
		return (false);
	return (true);
}

static bool	import_texture(t_texture *texture, const char *path)
{
	int			fd;
	uint32_t	size_tex;

	if (!(fd = open(path, O_RDONLY)))
		return (false);
	if (!(texture = ft_memalloc(sizeof(t_texture))))
	{
		close(fd);
		return (false);
	}
	if (!size_texture(texture, fd, &size_tex) ||
		!(texture->texture = ft_memalloc(size_tex)))
	{
		close(fd);
		return (false);
	}
	if ((read(fd, texture->texture, size_tex)) != size_tex)
	{
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

void			*texture_destroy(t_texture **texture)
{
	if (!texture || !*texture)
		return (NULL);
	if ((*texture)->texture)
		ft_memdel((void *)&(*texture)->texture);
	glDeleteTextures(1, &(*texture)->textureID);
	ft_memdel((void *)texture);
	return (NULL);
}

t_texture		*texture_construct(const char *texture_path)
{
	t_texture *texture;

	if (!(texture = ft_memalloc(sizeof(t_texture))))
		return (texture_destroy(&texture));
	if (!import_texture(texture, texture_path))
		return (texture_destroy(&texture));
	glGenTextures(1, &texture->textureID);
	glBindTexture(GL_TEXTURE_2D, texture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
								texture->width,
								texture->height,
								0, GL_RGBA, GL_UNSIGNED_BYTE,
								texture->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	return (texture);
}
