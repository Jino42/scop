/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_temp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:45:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/21 19:42:58 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

bool	obj_pars(t_asset *asset, const char * path_obj)
{
	int			fd;
	char		*line;
	char		type[10];
	int			index_v[4];
	int			index_vt[4];
	int			index_vn[4];
	float		v[4];
	float		vt[4];
	float		vn[4];

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
	asset->indices = ft_memalloc(10000000); ///////////////////////////////////////////////////
	///////////////////////////SIZEOF ? TES SUR ?
	int j = 0;
	uint32_t mem_len_indices = BUFFER_OBJ; (void)mem_len_indices;
	uint32_t mem_len_indexed_v = BUFFER_OBJ; (void)mem_len_indexed_v;
	uint32_t mem_len_indexed_vn = BUFFER_OBJ; (void)mem_len_indexed_vn;
	uint32_t mem_len_indexed_vt = BUFFER_OBJ; (void)mem_len_indexed_vt;
	uint32_t mem_len_v = BUFFER_OBJ; (void)mem_len_v;
	uint32_t mem_len_vt = BUFFER_OBJ; (void)mem_len_vt;
	uint32_t mem_len_vn = BUFFER_OBJ; (void)mem_len_vn;
	while (get_next_line(fd, &line) == 1)
	{
		sscanf(line, "%s ", type);
		if (!strcmp("#", type))
			;
		else if (!strcmp("vn", type))
		{
			asset->flag |= SCOP_VN;
			if (sscanf(line, "%s %f %f %f\n", type, &v[0], &v[1], &v[2]) != 4)
				return (false);
			asset->vn[3 * asset->nb_vn + 0] = v[0];
			asset->vn[3 * asset->nb_vn + 1] = v[1];
			asset->vn[3 * asset->nb_vn + 2] = v[2];
			asset->nb_vn++;
		}
		else if (!strcmp("vt", type))
		{
			asset->flag |= SCOP_VT;
			if (sscanf(line, "%s %f %f\n", type, &vt[0], &vt[1]) != 3)
				return (false);
			asset->vt[2 * asset->nb_vt + 0] = vt[0];
			asset->vt[2 * asset->nb_vt + 1] = vt[1];
			asset->nb_vt++;
		}
		else if (!strcmp("v", type))
		{
			asset->flag |= SCOP_V;
			if (sscanf(line, "%s %f %f %f\n", type, &vn[0], &vn[1], &vn[2]) != 4)
				return (false);
			asset->v[3 * asset->nb_v + 0] = vn[0];
			asset->v[3 * asset->nb_v + 1] = vn[1];
			asset->v[3 * asset->nb_v + 2] = vn[2];
			asset->nb_v++;
		}
		else if (!strcmp("f", type))
		{
			int ret = 0;
			if (asset->flag == SCOP_V)
			{
				ret = sscanf(line, "%s %i %i %i\n", type, &index_v[0], &index_v[1], &index_v[2]);
				if (ret != 4)
					return (false);
				ret = (ret - 1);
			}
			if (asset->flag == (SCOP_V | SCOP_VN))
			{
				ret = sscanf(line, "%s %i//%i %i//%i %i//%i %i//%i\n", type,
													&index_v[0], &index_vn[0],
													&index_v[1], &index_vn[1],
													&index_v[2], &index_vn[2],
													&index_v[3], &index_vn[3]);
				if (ret != 7 && ret != 9)
					return (false);
				ret = (ret - 1) >> 1;
			}
			if (asset->flag == (SCOP_V | SCOP_VT))
			{
				ret = sscanf(line, "%s %i/%i %i/%i %i/%i %i/%i\n", type,
													&index_v[0], &index_vt[0],
													&index_v[1], &index_vt[1],
													&index_v[2], &index_vt[2],
													&index_v[3], &index_vt[3]);
				if (ret != 7 && ret != 9)
					return (false);
				ret = (ret - 1) >> 1;
				ft_printf("Ret : [%i]\n", ret);
			}
			if (asset->flag == (SCOP_V | SCOP_VN | SCOP_VT))
			{
				ret = sscanf(line, "%s %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i\n", type,
													&index_v[0], &index_vt[0], &index_vn[0],
													&index_v[1], &index_vt[1], &index_vn[1],
													&index_v[2], &index_vt[2], &index_vn[2],
													&index_v[3], &index_vt[3], &index_vn[3]);
				if (ret != 10 && ret != 13)
					return (false);
				ret = (ret - 1) >> 2;
			}
			int sommet = 0;
			while (sommet < 3)
			{
				asset->indices[j] = j;
				if (asset->flag & SCOP_V)
				{
					asset->indexed_v[j * 3 + 0] = asset->v[(index_v[sommet] - 1) * 3 + 0];
					asset->indexed_v[j * 3 + 1] = asset->v[(index_v[sommet] - 1) * 3 + 1];
					asset->indexed_v[j * 3 + 2] = asset->v[(index_v[sommet] - 1) * 3 + 2];
					asset->nb_indexed_v++;
				}
				if (asset->flag & SCOP_VT)
				{
					asset->indexed_vt[j * 2 + 0] = asset->vt[(index_vt[sommet] - 1) * 2 + 0];
					asset->indexed_vt[j * 2 + 1] = asset->vt[(index_vt[sommet] - 1) * 2 + 1];
					asset->nb_indexed_vt++;
				}
				if (asset->flag & SCOP_VN)
				{
					asset->indexed_vn[j * 3 + 0] = asset->vn[(index_vn[sommet] - 1) * 3 + 0];
					asset->indexed_vn[j * 3 + 1] = asset->vn[(index_vn[sommet] - 1) * 3 + 1];
					asset->indexed_vn[j * 3 + 2] = asset->vn[(index_vn[sommet] - 1) * 3 + 2];
					asset->nb_indexed_vn++;
				}
				j++;
				sommet++;
			}
			asset->nb_indices += 3;
			asset->nb_faces += 1;
			if (ret == 4)
			{
				sommet = 0;
				while (sommet < 4)
				{
					if (sommet == 1)
						sommet++;
					asset->indices[j] = j;
					if (asset->flag & SCOP_V)
					{
						asset->indexed_v[j * 3 + 0] = asset->v[(index_v[sommet] - 1) * 3 + 0];
						asset->indexed_v[j * 3 + 1] = asset->v[(index_v[sommet] - 1) * 3 + 1];
						asset->indexed_v[j * 3 + 2] = asset->v[(index_v[sommet] - 1) * 3 + 2];
						asset->nb_indexed_v++;
					}
					if (asset->flag & SCOP_VT)
					{
						asset->indexed_vt[j * 2 + 0] = asset->vt[(index_vt[sommet] - 1) * 2 + 0];
						asset->indexed_vt[j * 2 + 1] = asset->vt[(index_vt[sommet] - 1) * 2 + 1];
						asset->nb_indexed_vt++;
					}
					if (asset->flag & SCOP_VN)
					{
						asset->indexed_vn[j * 3 + 0] = asset->vn[(index_vn[sommet] - 1) * 3 + 0];
						asset->indexed_vn[j * 3 + 1] = asset->vn[(index_vn[sommet] - 1) * 3 + 1];
						asset->indexed_vn[j * 3 + 2] = asset->vn[(index_vn[sommet] - 1) * 3 + 2];
						asset->nb_indexed_vn++;
					}
					j++;
					sommet++;
				}
				asset->nb_indices += 3;
				asset->nb_faces += 1;
			}
		}
		else if(!strcmp("mtllib", type))
			;
		else if (!strcmp("usemtl", type))
			;
		else if (!strcmp("o", type))
		{
			ft_printf("Cet object contient des groups\n");
			return (false);
		}
		ft_strdel(&line);/*
		if (j * sizeof(GLushort) >= mem_len_indices)
		{
			mem_len_indices += BUFFER_OBJ;
			asset->indices = realloc(asset->indices, mem_len_indices);
		}
		if (asset->nb_indexed_v * sizeof(GLfloat) * 3 >= mem_len_indexed_v)
		{
			mem_len_indexed_v += BUFFER_OBJ;
			asset->indexed_v = realloc(asset->indexed_v, mem_len_indexed_v);
		}
		if (asset->nb_indexed_vn * sizeof(GLfloat) * 3 >= mem_len_indexed_vn)
		{
			mem_len_indexed_vn += BUFFER_OBJ;
			asset->indexed_vn = realloc(asset->indexed_vn, mem_len_indexed_vn);
		}
		if (asset->nb_indexed_vt * sizeof(GLfloat) * 2 >= mem_len_indexed_vt)
		{
			mem_len_indexed_vt += BUFFER_OBJ;
			asset->indexed_vt = realloc(asset->indexed_vt, mem_len_indexed_vt);
		}
		if (asset->nb_v * sizeof(GLfloat) * 3 >= mem_len_v)
		{
			mem_len_v += BUFFER_OBJ;
			asset->v = realloc(asset->v, mem_len_v);
		}
		if (asset->nb_vt * sizeof(GLfloat) * 2 >= mem_len_vt)
		{
			mem_len_vt += BUFFER_OBJ;
			asset->vt = realloc(asset->vt, mem_len_vt);
		}
		if (asset->nb_vn * sizeof(GLfloat) * 3 >= mem_len_vn)
		{
			mem_len_vn += BUFFER_OBJ;
			asset->vn = realloc(asset->vn, mem_len_vn);
		}*/
	}
	printf("Pars end\n");
	return (true);
}
