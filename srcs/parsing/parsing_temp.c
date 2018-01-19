/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_temp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:45:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/19 23:25:11 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

bool	obj_pars(t_asset *asset, const char * path_obj)
{
	int		fd;
	char	*line;
	char	type[10];
	float	tab[4];
	int		tabi[4];

	fd = open(path_obj, O_RDONLY);
	if (!fd || fd < 0)
		return (false);
	line = NULL;
	for (int i = 0; i < 0; i++)
		get_next_line(fd, &line);
	asset->vertices = ft_memalloc(sizeof(GLfloat) * 10000000);
	asset->indices = ft_memalloc(sizeof(GLuint) * 10000000);
	int i = 0;
	int j = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (sscanf(line, "%s ", type) != 1)
			return (true);
		if (!strcmp("v", type))
		{
			if (sscanf(line, "%s %f %f %f\n", type, &tab[0], &tab[1], &tab[2]) != 4)
				return (true);
			asset->vertices[3 * i + 0] = tab[0];
			asset->vertices[3 * i + 1] = tab[1];
			asset->vertices[3 * i + 2] = tab[2];
			asset->nb_vertices++;
		}
		else if (!strcmp("f", type))
		{
			int ret = 0;
			ret = sscanf(line, "%s %i %i %i\n", type, &tabi[0], &tabi[1], &tabi[2]);
			asset->indices[j] = tabi[0] - 1;
			j++;
			asset->indices[j] = tabi[1] - 1;
			j++;
			asset->indices[j] = tabi[2] - 1;
			asset->nb_indices += 3;
			asset->nb_faces += 1;
			j++;
		}
		i++;
	}
	return (true);
}
