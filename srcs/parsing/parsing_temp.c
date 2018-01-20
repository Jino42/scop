/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_temp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:45:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/20 19:12:39 by ntoniolo         ###   ########.fr       */
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
	int		tabi[20];

	fd = open(path_obj, O_RDONLY);
	if (!fd || fd < 0)
		return (false);
	line = NULL;
	asset->v = ft_memalloc(sizeof(GLfloat) * 10000000);
	asset->vt = ft_memalloc(sizeof(GLfloat) * 10000000);
	asset->vn = ft_memalloc(sizeof(GLfloat) * 10000000);
	asset->indexed_v = ft_memalloc(sizeof(GLfloat) * 10000000);
	asset->indexed_vt = ft_memalloc(sizeof(GLfloat) * 10000000);
	asset->indexed_vn = ft_memalloc(sizeof(GLfloat) * 10000000);
	asset->indices = ft_memalloc(sizeof(GLushort) * 10000000);
	int j = 0;
	while (get_next_line(fd, &line) == 1)
	{
		sscanf(line, "%s ", type);
		if (!strcmp("#", type))
			;
		else if (!strcmp("vn", type))
		{
			asset->flag |= SCOP_VN;
			if (sscanf(line, "%s %f %f %f\n", type, &tab[0], &tab[1], &tab[2]) != 4)
				return (true);
			asset->vn[3 * asset->nb_vn + 0] = tab[0];
			asset->vn[3 * asset->nb_vn + 1] = tab[1];
			asset->vn[3 * asset->nb_vn + 2] = tab[2];
			asset->nb_vn++;
		}
		else if (!strcmp("vt", type))
		{
			asset->flag |= SCOP_VT;
			if (sscanf(line, "%s %f %f\n", type, &tab[0], &tab[1]) != 3)
				return (true);
			asset->vt[2 * asset->nb_vt + 0] = tab[0];
			asset->vt[2 * asset->nb_vt + 1] = tab[1];
			asset->nb_vt++;
		}
		else if (!strcmp("v", type))
		{
			asset->flag |= SCOP_V;
			if (sscanf(line, "%s %f %f %f\n", type, &tab[0], &tab[1], &tab[2]) != 4)
				return (true);
			asset->v[3 * asset->nb_v + 0] = tab[0];
			asset->v[3 * asset->nb_v + 1] = tab[1];
			asset->v[3 * asset->nb_v + 2] = tab[2];
			asset->nb_v++;
		}
		else if (!strcmp("f", type))
		{
			int ret = 0;
			if (asset->flag == SCOP_V)
			{
				ret = sscanf(line, "%s %i %i %i\n", type, &tabi[0], &tabi[1], &tabi[2]);
				asset->indices[j] = j;
				asset->indexed_v[j*3+0] = asset->v[(tabi[0] - 1)*3];
				asset->indexed_v[j*3+1] = asset->v[(tabi[0] - 1)*3 + 1];
				asset->indexed_v[j*3+2] = asset->v[(tabi[0] - 1)*3 + 2];
				j++;
				asset->indices[j] = j;
				asset->indexed_v[j*3+0] = asset->v[(tabi[1] - 1)*3];
				asset->indexed_v[j*3+1] = asset->v[(tabi[1] - 1)*3 + 1];
				asset->indexed_v[j*3+2] = asset->v[(tabi[1] - 1)*3 + 2];
				j++;
				asset->indices[j] = j;
				asset->indexed_v[j*3+0] = asset->v[(tabi[2] - 1)*3];
				asset->indexed_v[j*3+1] = asset->v[(tabi[2] - 1)*3 + 1];
				asset->indexed_v[j*3+2] = asset->v[(tabi[2] - 1)*3 + 2];
				j++;
				asset->nb_indices += 3;
			}
			if (asset->flag == (SCOP_V | SCOP_VN))
			{
				ret = sscanf(line, "%s %i//%i %i//%i %i//%i\n", type, &tabi[0], &tabi[1], &tabi[2], &tabi[3], &tabi[4], &tabi[5]);
				asset->indices[j] = j;
				asset->indexed_v[j*3+0] = asset->v[(tabi[0] - 1)*3];
				asset->indexed_v[j*3+1] = asset->v[(tabi[0] - 1)*3 + 1];
				asset->indexed_v[j*3+2] = asset->v[(tabi[0] - 1)*3 + 2];
				asset->indexed_vn[j*3+0] = asset->vn[(tabi[1] - 1)*3];
				asset->indexed_vn[j*3+1] = asset->vn[(tabi[1] - 1)*3 + 1];
				asset->indexed_vn[j*3+2] = asset->vn[(tabi[1] - 1)*3 + 2];
				j++;
				//asset->indices[j++] = tabi[1] - 1;
				asset->indices[j] = j;
				asset->indexed_v[j*3+0] = asset->v[(tabi[2] - 1)*3];
				asset->indexed_v[j*3+1] = asset->v[(tabi[2] - 1)*3 + 1];
				asset->indexed_v[j*3+2] = asset->v[(tabi[2] - 1)*3 + 2];
				asset->indexed_vn[j*3+0] = asset->vn[(tabi[3] - 1)*3];
				asset->indexed_vn[j*3+1] = asset->vn[(tabi[3] - 1)*3 + 1];
				asset->indexed_vn[j*3+2] = asset->vn[(tabi[3] - 1)*3 + 2];
				j++;
				//asset->indices[j++] = tabi[3] - 1;
				asset->indices[j] = j;
				asset->indexed_v[j*3+0] = asset->v[(tabi[4] - 1)*3];
				asset->indexed_v[j*3+1] = asset->v[(tabi[4] - 1)*3 + 1];
				asset->indexed_v[j*3+2] = asset->v[(tabi[4] - 1)*3 + 2];
				asset->indexed_vn[j*3+0] = asset->vn[(tabi[5] - 1)*3];
				asset->indexed_vn[j*3+1] = asset->vn[(tabi[5] - 1)*3 + 1];
				asset->indexed_vn[j*3+2] = asset->vn[(tabi[5] - 1)*3 + 2];
				j++;
				//asset->indices[j++] = tabi[5] - 1;
				asset->nb_indices += 3;
			}
			if (asset->flag == (SCOP_V | SCOP_VN | SCOP_VT))
			{
				ret = sscanf(line, "%s %i/%i/%i %i/%i/%i %i/%i/%i\n", type, &tabi[0], &tabi[1], &tabi[2], &tabi[3], &tabi[4], &tabi[5], &tabi[6], &tabi[7], &tabi[8]);
				asset->indices[j++] = tabi[0] - 1;
				//asset->indices[j++] = tabi[1] - 1;
				//asset->indices[j++] = tabi[2] - 1;
				asset->indices[j++] = tabi[3] - 1;
				//asset->indices[j++] = tabi[4] - 1;
				//asset->indices[j++] = tabi[5] - 1;
				asset->indices[j++] = tabi[6] - 1;
				//asset->indices[j++] = tabi[7] - 1;
				//asset->indices[j++] = tabi[8] - 1;
				asset->nb_indices += 9;
			}
			asset->nb_faces += 1;
		}
		else if(!strcmp("mtllib", type))
			;
		else if (!strcmp("usemtl", type))
			;
		ft_strdel(&line);
	}
	return (true);
}
