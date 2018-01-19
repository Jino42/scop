/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 22:16:06 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/19 22:50:26 by ntoniolo         ###   ########.fr       */
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

bool	import_texture(t_texture *texture, const char *path)
{
	int			fd;
	uint32_t	size_tex;

	if (!(fd = open(path, O_RDONLY)))
		return (false);
	if (!(texture = ft_memalloc(sizeof(t_texture))))
		return (false);
	if (!size_texture(texture, fd, &size_tex) ||
		!(texture->texture = ft_memalloc(size_tex)))
	{
		ft_memdel((void *)&texture);
		return (false);
	}
	if ((read(fd, texture->texture, size_tex)) != size_tex)
	{
		ft_memdel((void *)&texture->texture);
		ft_memdel((void *)&texture);
		return (false);
	}
	return (true);
}
