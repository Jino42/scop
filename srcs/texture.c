/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 22:16:06 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/30 23:46:29 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static bool	size_texture(t_tex *tex, const int fd, uint32_t *size_tex)
{
	read(fd, &tex->width, sizeof(uint32_t));
	read(fd, &tex->height, sizeof(uint32_t));
	*size_tex = tex->width * tex->height * 4;
	if (tex->width > 4996 || tex->height > 4996)
		return (false);
	return (true);
}

static unsigned char	*import_texture(t_tex *tex, const char *path)
{
	unsigned char	*data_tex;
	int				fd;
	uint32_t		size_tex;

	if (!(fd = open(path, O_RDONLY)))
		return (NULL);
	if (!size_texture(tex, fd, &size_tex) ||
		!(data_tex = ft_memalloc(size_tex)))
	{
		close(fd);
		return (NULL);
	}
	if ((read(fd, data_tex, size_tex)) != size_tex)
	{
		ft_memdel((void *)data_tex);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (data_tex);
}

void			*textures_destroy(t_textures **textures)
{
	if (!textures || !*textures)
		return (NULL);
	ft_memdel((void *)textures);
	return (NULL);
}

void			*tex_destroy(t_tex **tex)
{
	if (!tex || !*tex)
		return (NULL);
	ft_memdel((void*)tex);
	return (NULL);
}
t_tex			*tex_construct(const char *tex_path)
{
	t_tex			*tex;
	unsigned char	*data_tex;

	if (!(tex = ft_memalloc(sizeof(t_tex))))
		return (NULL);
	if (!(data_tex = import_texture(tex, tex_path)))
		return (tex_destroy(&tex));
	glGenTextures(1, &tex->id);
	glBindTexture(GL_TEXTURE_2D, tex->id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
								tex->width,
								tex->height,
								0, GL_BGRA, GL_UNSIGNED_BYTE,
								data_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	ft_memdel((void *)&data_tex);
	return (tex);
}

bool	texture_add(t_textures *textures,
				const char *texture_path)
{
	if (!(textures->texture = realloc(textures->texture, sizeof(t_tex **) * (textures->size + 1))))
		return (false);
	textures->texture[textures->size] = tex_construct(texture_path);
	textures->size++;
	return (true);
}
/*
void	texture_set(const t_texture *textures,
					const t_mesh *mesh,
					const t_shader *shader,
					const char *name_uniform)
{
	glUniform1i(glGetUniformLocation(shader->program, name_uniform), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->tex->id);
}*/

t_textures		*textures_construct()
{
	t_textures		*textures;

	if (!(textures = ft_memalloc(sizeof(t_textures))))
		return (textures_destroy(&textures));
	textures->add = &texture_add;
	return (textures);
}
